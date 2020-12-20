from gpiozero import Button
from gpiozero import LED
import math
import time

start_stop_button_pin = 17
led_pin = 4

start_stop_button = Button(start_stop_button_pin, bounce_time=0.05)
led = LED(led_pin)

start_time = 0.0
is_active = False
min = 0
sec = 0
x = 0


def time_converter(sec):
    global min
    global sec2
    global x
    min = (sec % 3600) / 60
    min = math.floor(min)
    sec2 = math.floor(sec)
    x = (sec - sec2)*1000
    x = math.floor(x)


def start():
    global is_active
    global start_time
    is_active = True
    start_time = 0.0
    start_time = time.perf_counter()
    print('計測が開始されました。')
    led.toggle()


def stop():
    global is_active
    is_active = False
    led.toggle()
    print('計測が終了されました。')
    time_end = time.perf_counter()
    diff_time = time_end - start_time
    time_converter(diff_time)
    report = str(min) + '分' + str(sec2) + '秒' + str(x) + 'ミリ秒'
    print(report)
    time_end = 0.0


def switch():
    if is_active == False:
        start()
    elif is_active == True:
        stop()


def main_loop():
    global is_active
    if is_active == False:
        start_stop_button.when_pressed = switch
    while True:
        pass


if __name__ == '__main__':
    main_loop()
