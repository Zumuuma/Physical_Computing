from gpiozero import Button
from gpiozero import LED

button = Button(17, bounce_time=0.05)
led = LED(27)


def toggle_led():
    print('pressed')
    led.toggle()


def main_loop():
    button.when_pressed = toggle_led
    while True:
        pass


if __name__ == '__main__':
    main_loop()
