#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define PIN_1 0 //０番ポート使用。ラズパイ１１番ピンに接続。
#define PIN_2 3 //３番ポート使用。ラズパイ１５番ピンに接続。
#define PIN_3 7 //７番ポート使用。ラズパイ７番ピンに接続。

int leds[3] = {PIN_1, PIN_2, PIN_3};

void convert_from_10_to_2(int num) //１０進数から２進数に変換してLEDを光らせる関数
{
	for (int i = 2; i >= 0; i--)
	{
		if (num % 2 == 1)
		{
			digitalWrite(leds[i], HIGH);
		}
		else if (num % 2 == 0)
		{
			digitalWrite(leds[i], LOW);
		}
		num = num / 2; //変換したい１０進数を２で割る
	}
}

void loop()
{
	int num = 0;

	for (;;)
	{
		convert_from_10_to_2(num);

		delay(500); //xの値をインクリメントするまでの時間(ミリ秒)

		num = num + 1; //xの値をインクリメント

		if (num == 8) //xの値が８ならxの値を０に戻す
		{
			num = 0;
		}
	}
}

int main(void)
{
	wiringPiSetup();		//https://projects.drogon.net/raspberry-pi/wiringpi/pins/を参照してポート番号を照らし合わせる。
	pinMode(PIN_1, OUTPUT); //出力モード
	pinMode(PIN_2, OUTPUT); //出力モード
	pinMode(PIN_3, OUTPUT); //出力モード

	loop();

	return 0;
}