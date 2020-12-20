from time import sleep
from adc_8chan_12bit import Pi_hat_adc

adc = Pi_hat_adc()


def main_loop():
    while True:
        print(adc.get_nchan_adc_raw_data(0))
        sleep(0.5)


if __name__ == '__main__':
    main_loop()
