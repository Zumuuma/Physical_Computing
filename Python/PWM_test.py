from gpiozero import PWMLED
from time import sleep

led_pin = 17

led_pwm = PWMLED(led_pin)


def main_loop():
    while True:
        led_pwm.value = 0.8  # デューティ比80%
        sleep(0.5)
        led_pwm.value = 0.1  # デューティ比10%
        sleep(0.5)


if __name__ == '__main__':
    main_loop()
