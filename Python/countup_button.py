from gpiozero import LED
from gpiozero import Button

led_pin1 = 22
led_pin2 = 27
led_pin3 = 17

button = Button(4, bounce_time=0.05)

y = 0

leds = [LED(led_pin1),
        LED(led_pin2),
        LED(led_pin3)]


def bin_led(num):
    for i in range(3):
        a = num % 2
        num = num // 2
        if a == 1:
            leds[i].on()
        if a == 0:
            leds[i].off()


def toggle_led():
    global y
    if y > 7:
        y = 0
        bin_led(y)
    y = y + 1


def main_loop():
    button.when_pressed = toggle_led
    while True:
        pass


if __name__ == '__main__':
    main_loop()
