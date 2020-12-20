from gpiozero import Button
from time import sleep

button = Button(17, pull_up=None, active_state=True)


def main_loop():
    while True:
        if button.is_pressed:
            print('pressed')
        else:
            print('not pressed')
        sleep(0.1)


if __name__ == '__main__':
    main_loop()
