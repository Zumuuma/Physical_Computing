import requests
from time import sleep

api_key = 'API_KEY'
url = 'https://api.thingspeak.com/channels/1225088/feeds.json'


def rec_data():
    data = []
    response = requests.get(url,
                            params={
                                'api_key': api_key,
                                'timezone': 'Asia/Tokyo',
                                'results': 5
                            })
    response_list = response.json()['feeds']

    for elm in response_list:
        data.append(elm['field1'])
    print(data)


def main_loop():
    rec_data()


if __name__ == '__main__':
    main_loop()
