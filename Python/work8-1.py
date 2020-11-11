import requests
from time import sleep
from adc_8chan_12bit import Pi_hat_adc

adc = Pi_hat_adc()
api_key = '60F7C0A20Z0DG18N'
url = 'https://api.thingspeak.com/update'


def send_data(brightness):
    response = requests.get(url,
                            params={
                                'api_key': api_key,
                                'field1': brightness
                            })
    print(response.json)


def main_loop():
    while True:
        brightness = adc.get_nchan_adc_raw_data(0)
        print(brightness)
        send_data(brightness)
        sleep(30)


if __name__ == '__main__':
    main_loop()
