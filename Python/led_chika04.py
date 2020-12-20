from gpiozero import LED
from time import sleep

led_pin1 = 17
led_pin2 = 22
led_pin3 = 4

leds = [LED(led_pin1),
        LED(led_pin2),
        LED(led_pin3,)]


def main_loop():
    while True:
        x = 5
        for i in range(3):
            a = x % 2
            x = x // 2
            if a == 1:
                leds[i].on()


if __name__ == '__main__':
    main_loop()
