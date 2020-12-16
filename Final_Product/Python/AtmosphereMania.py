# @author: Souichirou Kikuchi.(bme280_lcd.py)
# Copyright (c) Microsoft. All rights reserved.(SimulatedDevice.py)
# Licensed under the MIT license. See LICENSE file in the project root for full license information.
# Last edited by かとぽよ<Katopoyo>.(AtmosphereMania.py)

import time
from gpiozero import LED
from smbus2 import SMBus
import Adafruit_SSD1306
import Adafruit_GPIO.SPI as SPI
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont


# Using the Python Device SDK for IoT Hub:
#   https://github.com/Azure/azure-iot-sdk-python
# The sample connects to a device-specific MQTT endpoint on your IoT Hub.
from azure.iot.device import IoTHubDeviceClient, Message

# The device connection string to authenticate the device with your IoT hub.
# Using the Azure CLI:
# az iot hub device-identity show-connection-string --hub-name {YourIoTHubName} --device-id MyNodeDevice --output table
CONNECTION_STRING = "Connection_String(PRIMARY_KEY)"

# Define the JSON message to send to IoT Hub.
MSG_TXT = '{{"temperature": {temperature},"humidity": {humidity},"pressure": {pressure}}}'

BME280_BUS_NUMBER = 1
BME280_I2C_ADDRESS = 0x76  # BME280のI2Cのアドレス
I2C_SPI = 'i2c'  # LCDをI2Cで接続する
LCD_RST = None  # リセットしたいGPIOのピン番号を指定する
DISPLAY_WITH = '128x64'  # LCDのディスプレイの解像度
LCD_I2C_ADDRESS = 0x3C  # LCDのI2Cのアドレス
LCD_I2C_BUS_NUMBER = 1  # LCDのI2CのBUS番号


class Bme280Class:  # 温湿度気圧センサー（BME280）クラス

    def __init__(self, bus_number, i2c_address):  # コンストラクタ（初期処理）
        self.bus = SMBus(bus_number)
        self.dig_temp = []
        self.dig_pres = []
        self.dig_humi = []
        self.t_fine = 0.0
        __osrs_t = 1  # Temperature oversampling x 1
        __osrs_p = 1  # Pressure oversampling x 1
        __osrs_h = 1  # Humidity oversampling x 1
        __mode = 3  # Normal mode
        __t_sb = 5  # Tstandby 1000ms
        __filter = 0  # Filter off
        __spi3w_en = 0  # 3-wire SPI Disable

        __ctrl_meas_reg = (__osrs_t << 5) | (__osrs_p << 2) | __mode
        __config_reg = (__t_sb << 5) | (__filter << 2) | __spi3w_en
        __ctrl_hum_reg = __osrs_h
        self.write_reg(i2c_address, 0xF2, __ctrl_hum_reg)
        self.write_reg(i2c_address, 0xF4, __ctrl_meas_reg)
        self.write_reg(i2c_address, 0xF5, __config_reg)
        self.get_calib_param(i2c_address)

    def get_calib_param(self, i2c_address):
        __calib = []
        for i in range(0x88, 0x88+24):
            __calib.append(self.bus.read_byte_data(i2c_address, i))
        __calib.append(self.bus.read_byte_data(i2c_address, 0xA1))
        for i in range(0xE1, 0xE1+7):
            __calib.append(self.bus.read_byte_data(i2c_address, i))
        self.dig_temp.append((__calib[1] << 8) | __calib[0])
        self.dig_temp.append((__calib[3] << 8) | __calib[2])
        self.dig_temp.append((__calib[5] << 8) | __calib[4])
        self.dig_pres.append((__calib[7] << 8) | __calib[6])
        self.dig_pres.append((__calib[9] << 8) | __calib[8])
        self.dig_pres.append((__calib[11] << 8) | __calib[10])
        self.dig_pres.append((__calib[13] << 8) | __calib[12])
        self.dig_pres.append((__calib[15] << 8) | __calib[14])
        self.dig_pres.append((__calib[17] << 8) | __calib[16])
        self.dig_pres.append((__calib[19] << 8) | __calib[18])
        self.dig_pres.append((__calib[21] << 8) | __calib[20])
        self.dig_pres.append((__calib[23] << 8) | __calib[22])
        self.dig_humi.append(__calib[24])
        self.dig_humi.append((__calib[26] << 8) | __calib[25])
        self.dig_humi.append(__calib[27])
        self.dig_humi.append((__calib[28] << 4) | (0x0F & __calib[29]))
        self.dig_humi.append((__calib[30] << 4) | ((__calib[29] >> 4) & 0x0F))
        self.dig_humi.append(__calib[31])
        for i in range(1, 2):
            if self.dig_temp[i] & 0x8000:
                self.dig_temp[i] = (-self.dig_temp[i] ^ 0xFFFF) + 1
        for i in range(1, 8):
            if self.dig_pres[i] & 0x8000:
                self.dig_pres[i] = (-self.dig_pres[i] ^ 0xFFFF) + 1
        for i in range(0, 6):
            if self.dig_humi[i] & 0x8000:
                (-self.dig_humi[i] ^ 0xFFFF) + 1

    def read_data(self, i2c_address):
        __data = []
        for i in range(0xF7, 0xF7+8):
            __data.append(self.bus.read_byte_data(i2c_address, i))
        __pres_raw = (__data[0] << 12) | (__data[1] << 4) | (__data[2] >> 4)
        __temp_raw = (__data[3] << 12) | (__data[4] << 4) | (__data[5] >> 4)
        __humi_raw = (__data[6] << 8) | __data[7]
        __temp = self.compensate_temp(__temp_raw)  # 温度を計算
        __pres = self.compensate_pres(__pres_raw)  # 気圧を計算
        __humi = self.compensate_humi(__humi_raw)  # 湿度を計算
        return __temp, __pres, __humi

    def write_reg(self, i2c_address, reg_address, data):
        self.bus.write_byte_data(i2c_address, reg_address, data)

    def compensate_pres(self, adc_pres):
        __pressure = 0.0
        __v1 = (self.t_fine / 2.0) - 64000.0
        __v2 = (((__v1 / 4.0) * (__v1 / 4.0)) / 2048) * self.dig_pres[5]
        __v2 = __v2 + ((__v1 * self.dig_pres[4]) * 2.0)
        __v2 = (__v2 / 4.0) + (self.dig_pres[3] * 65536.0)
        __v1 = (((self.dig_pres[2] * (((__v1 / 4.0) * (__v1 / 4.0)) / 8192)
                  ) / 8) + ((self.dig_pres[1] * __v1) / 2.0)) / 262144
        __v1 = ((32768 + __v1) * self.dig_pres[0]) / 32768

        if __v1 == 0:
            return 0
        __pressure = ((1048576 - adc_pres) - (__v2 / 4096)) * 3125
        if __pressure < 0x80000000:
            __pressure = (__pressure * 2.0) / __v1
        else:
            __pressure = (__pressure / __v1) * 2
        __v1 = (self.dig_pres[8] * (((__pressure / 8.0)
                                     * (__pressure / 8.0)) / 8192.0)) / 4096
        __v2 = ((__pressure / 4.0) * self.dig_pres[7]) / 8192.0
        __pressure = __pressure + ((__v1 + __v2 + self.dig_pres[6]) / 16.0)
        return __pressure / 100

    def compensate_temp(self, adc_temp):
        __v1 = (adc_temp / 16384.0 -
                self.dig_temp[0] / 1024.0) * self.dig_temp[1]
        __v2 = (adc_temp / 131072.0 - self.dig_temp[0] / 8192.0) * (
            adc_temp / 131072.0 - self.dig_temp[0] / 8192.0) * self.dig_temp[2]
        self.t_fine = __v1 + __v2
        __temperature = self.t_fine / 5120.0
        return __temperature

    def compensate_humi(self, adc_humi):
        __var_h = self.t_fine - 76800.0
        if __var_h != 0:
            __var_h = (adc_humi - (self.dig_humi[3] * 64.0 + self.dig_humi[4]/16384.0 * __var_h)) * (self.dig_humi[1] / 65536.0 * (
                1.0 + self.dig_humi[5] / 67108864.0 * __var_h * (1.0 + self.dig_humi[2] / 67108864.0 * __var_h)))
        else:
            return 0
        __var_h = __var_h * (1.0 - self.dig_humi[0] * __var_h / 524288.0)
        if __var_h > 100.0:
            __var_h = 100.0
        elif __var_h < 0.0:
            __var_h = 0.0
        return __var_h


class LCD1306class:  # LCD1306クラス
    """
    I2C:i2c_or_spi='i2c',rst, display_with, i2c_address, i2c_bus を指定する
    SPI:i2c_or_spi='spi',rst, display_with, dc, spi_port, spi_device を指定する
    SoftwareSPI:i2c_or_spi='softspi',rst, display_with, dc, sclk, din, cs を指定する
    """

    def __init__(self, i2c_or_spi, rst, display_with, i2c_address, i2c_bus, dc=23, spi_port=0, spi_device=0, sclk=18, din=25, cs=22):  # コンストラクタ（初期処理）
        if i2c_or_spi == 'i2c':
            if display_with == '128x32':
                self.disp = Adafruit_SSD1306.SSD1306_128_32(
                    rst=rst, i2c_address=i2c_address, i2c_bus=i2c_bus)
            elif display_with == '128x64':
                self.disp = Adafruit_SSD1306.SSD1306_128_64(
                    rst=rst, i2c_address=i2c_address, i2c_bus=i2c_bus)
        elif i2c_or_spi == 'spi':
            if display_with == '128x32':
                self.disp = Adafruit_SSD1306.SSD1306_128_32(
                    rst=rst, dc=dc, spi=SPI.SpiDev(spi_port, spi_device, max_speed_hz=8000000))
            elif display_with == '128x64':
                self.isp = Adafruit_SSD1306.SSD1306_128_64(
                    rst=rst, dc=dc, spi=SPI.SpiDev(spi_port, spi_device, max_speed_hz=8000000))
        elif i2c_or_spi == 'softspi':
            if display_with == '128x32':
                self.disp = Adafruit_SSD1306.SSD1306_128_32(
                    rst=rst, dc=dc, sclk=sclk, din=din, cs=cs)
            elif display_with == '128x64':
                self.disp = Adafruit_SSD1306.SSD1306_128_64(
                    rst=rst, dc=dc, sclk=sclk, din=din, cs=cs)
        self.disp.begin()  # 初期化
        self.disp_clear()  # ディスプレイクリア
        self.width = self.disp.width  # ディスプレイの幅と高さを取得する
        self.height = self.disp.height
        self.image = Image.new('1', (self.width, self.height))  # 1: 白黒モード指定
        self.draw = ImageDraw.Draw(self.image)  # draw
        self.font = ImageFont.load_default()  # デフォルトフォント

    def draw_background(self, outline):  # 背景を黒く塗りつぶし(0:黒、255：白)
        if outline == True:  # 外枠を表示するかどうか
            __outline = 255
        else:
            __outline = 0
        self.draw.rectangle(
            (0, 0, self.width-1, self.height-1), outline=__outline, fill=0)

    def draw_text(self, x_axis, y_axis, draw_text):  # 指定座標に文字を白（255）でdraw
        self.draw.text((x_axis, y_axis), draw_text, font=self.font, fill=255)

    def disp_display(self):  # ディスプレイ表示
        self.disp.image(self.image)
        self.disp.display()

    def disp_clear(self):  # ディスプレイクリア
        self.disp.clear()
        self.disp.display()


def iothub_client_init():
    # Create an IoT Hub client
    client = IoTHubDeviceClient.create_from_connection_string(
        CONNECTION_STRING)
    return client


def iothub_client_telemetry():
    # Build the message with simulated telemetry values.
    temperature = temp
    humidity = humi
    pressure = pres
    msg_txt_formatted = MSG_TXT.format(
        temperature=temperature, humidity=humidity, pressure=pressure)
    message = Message(msg_txt_formatted)

    # Add a custom application property to the message.
    # An IoT hub can filter on these properties without access to the message body.
    if temperature > 30:
        message.custom_properties["temperatureAlert"] = "true"
    else:
        message.custom_properties["temperatureAlert"] = "false"

    # Send the message.
    print("Sending message: {}".format(message))
    client.send_message(message)
    print("Message successfully sent")


if __name__ == '__main__':
    try:
        print('--- program start ---')
        led = LED(26)  # 動作ランプLED用の変数
        bme280 = Bme280Class(BME280_BUS_NUMBER, BME280_I2C_ADDRESS)
        lcd1306 = LCD1306class(
            I2C_SPI, LCD_RST, DISPLAY_WITH, LCD_I2C_ADDRESS, LCD_I2C_BUS_NUMBER)
        client = iothub_client_init()  # iothub_client_telemetry関数の中で１度だけ実行する動作
        while True:
            led.on()  # リフレッシュLEDをオン
            temp, pres, humi = bme280.read_data(
                BME280_I2C_ADDRESS)  # 温湿度、気圧を取得
            # print ('temp: {:-6.2f} c'.format(temp))
            # print ('humi : {:6.2f} %'.format(humi))
            # print ('pres : {:7.2f} hPa'.format(pres))
            __outline = True  # 外枠表示
            lcd1306.draw_background(__outline)  # 背景描画
            x_axis = 5
            y_axis = 5
            draw_text = 'temp : {:-6.2f} c'.format(temp)
            lcd1306.draw_text(x_axis, y_axis, draw_text)  # 温度を表示
            y_axis = y_axis + 16
            draw_text = 'humi : {:6.2f} %'.format(humi)
            lcd1306.draw_text(x_axis, y_axis, draw_text)  # 湿度を表示
            y_axis = y_axis + 16
            draw_text = 'pres : {:7.2f} hPa'.format(pres)
            lcd1306.draw_text(x_axis, y_axis, draw_text)  # 気圧を表示
            lcd1306.disp_display()  # Displayに表示する
            iothub_client_telemetry()  # Azureにデータ飛ばす
            led.off()  # リフレッシュLEDオフ
            time.sleep(15)  # １５秒間隔で一連のループ動作を実行
    except KeyboardInterrupt:
        pass
    finally:
        lcd1306.disp_clear()  # 画面消す
        print('--- program end ---')
