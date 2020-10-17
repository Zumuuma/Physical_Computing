from gpiozero import LED
from time import sleep


led_pin1 = 17
led_pin2 = 22
led_pin3 = 27

leds = [LED(led_pin1),
        LED(led_pin2),
        LED(led_pin3)]


def main_loop():
    while True:
        leds[0].on()
        sleep(0.5)
        leds[0].off()
        sleep(0.5)
        leds[1].on()
        sleep(0.5)
        leds[1].off()
        sleep(0.5)
        leds[2].on()
        sleep(0.5)
        leds[2].off()
        sleep(0.5)


if __name__ == '__main__':
    main_loop()
