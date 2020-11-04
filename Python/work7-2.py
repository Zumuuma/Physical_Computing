from time import sleep
from gpiozero import LED
from adc_8chan_12bit import Pi_hat_adc

adc = Pi_hat_adc()
led = LED(17)


def main_loop():
    while True:
        brightness = adc.get_nchan_adc_raw_data(0)
        print(adc.get_nchan_adc_raw_data(0))
        if brightness <= 2000:
            led.on()
        elif brightness > 2000:
            led.off()
        sleep(0.5)


if __name__ == '__main__':
    main_loop()
