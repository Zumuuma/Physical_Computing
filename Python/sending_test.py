import requests
from time import sleep

api_key = 'API_KEY'
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
        brightness = 3333
        print(brightness)
        send_data(brightness)
        sleep(30)


if __name__ == '__main__':
    main_loop()
