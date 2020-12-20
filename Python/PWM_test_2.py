from gpiozero import PWMLED
from time import sleep

led_pin = 17

led_pwm = PWMLED(led_pin)


def main_loop():
    duty_ratio = 0.0  # デューティー比の初期値
    while True:
        led_pwm.value = duty_ratio
        duty_ratio += 0.05   # 5%ずつ増やしていく
        sleep(0.1)
        if duty_ratio >= 1.0:
            duty_ratio = 0  # 100%以上になったら0に戻す


if __name__ == '__main__':
    main_loop()
