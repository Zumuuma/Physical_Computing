from time import sleep
from gpiozero import PWMLED
from gpiozero import Button

led_pin = 18
A_pin = 4
B_pin = 22

A = Button(A_pin, bounce_time=0.05)
B = Button(B_pin, bounce_time=0.05)


led_pwm = PWMLED(led_pin, frequency=100)

duty_ratio = 0.0  # デューティー比の初期値


def light_up():
    global duty_ratio
    led_pwm.value = duty_ratio
    duty_ratio += 0.05   # 5%ずつ増やしていく
    if duty_ratio > 1.0:
        duty_ratio = 1.0  # 100%以上になったら0に戻す


def light_down():
    global duty_ratio
    led_pwm.value = duty_ratio
    duty_ratio -= 0.05   # 5%ずつ減らしていく
    if duty_ratio < 0:
        duty_ratio = 0  # 0%以下になったら0に戻す


def main_loop():
    global duty_ratio
    A.when_pressed = light_up
    B.when_pressed = light_down
    while True:
        pass


if __name__ == '__main__':
    main_loop()
