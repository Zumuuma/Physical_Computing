from gpiozero import LED
from time import sleep

led = LED(17, active_high=False)


def main_loop():
    while True:
        led.off()
        sleep(1)
        led.on()
        sleep(1)


if __name__ == '__main__':
    main_loop()
