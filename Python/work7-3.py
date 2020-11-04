from time import sleep
from gpiozero import LED
from gpiozero import PWMLED
from adc_8chan_12bit import Pi_hat_adc

led_pin = 17
adc = Pi_hat_adc()
led_pwm = PWMLED(led_pin)


def main_loop():
    while True:
        brightness = adc.get_nchan_adc_raw_data(0)
        print(adc.get_nchan_adc_raw_data(0))
        if brightness <= 1000:
            led_pwm.value = 1.0
        elif brightness <= 1500:
            led_pwm.value = 0.8
        elif brightness <= 2000:
            led_pwm.value = 0.6
        elif brightness <= 2500:
            led_pwm.value = 0.4
        else:
            led_pwm.value = 0.2
        sleep(0.5)


if __name__ == '__main__':
    main_loop()
