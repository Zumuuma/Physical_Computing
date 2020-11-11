import requests
from time import sleep

api_key = '0PNGGPVT4PU6H5K8'
url = 'https://api.thingspeak.com/channels/1225088/feeds.json'


def rec_data():
    response = requests.get(url,
                            params={
                                'api_key': api_key,
                                'timezone': 'Asia/Tokyo',
                                'results': 2
                            })
    response_list = response.json()['feeds']
    print(response_list)


def main_loop():
    rec_data()


if __name__ == '__main__':
    main_loop()
