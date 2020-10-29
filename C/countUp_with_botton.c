#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define PIN_1 0	 //０番ポート使用。ラズパイ１１番ピンに接続。
#define PIN_2 2	 //２番ポート使用。ラズパイ１３番ピンに接続。
#define PIN_3 3	 //３番ポート使用。ラズパイ１５番ピンに接続。
#define BUTTON 7 //１番ポート使用。ラズパイ１２番ピンに接続。

int val = 0;	 //入力ピンの状態がこの変数(val)に記憶される
int old_val = 0; //valの前の値を保存しておく変数
int leds[3] = {PIN_1, PIN_2, PIN_3};

void convert_from_10_to_2(int num) //１０進数から２進数に変換してLEDを光らせる関数
{
	for (int i = 0; i < 3; i++)
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
	int count = 0; //ボタンが押された回数を記憶

	for (;;)
	{
		val = digitalRead(BUTTON); //入力を読みvalに新鮮な値を保存

		if ((val == HIGH) && (old_val == LOW)) //ボタンが押されたら
		{
			count = 1 + count; //カウントアップする
			delay(200);		   //デバウンシング処理
		}

		old_val = val; //古いvalはここに保管

		convert_from_10_to_2(count);

		if (count == 8) //countの値が８ならcountの値を０に戻す
		{
			count = 0;
		}
	}
}

int main(void)
{
	wiringPiSetup();		//https://projects.drogon.net/raspberry-pi/wiringpi/pins/を参照してポート番号を照らし合わせる。
	pinMode(BUTTON, INPUT); //BUTTONは入力に設定
	pinMode(PIN_1, OUTPUT); //出力モード
	pinMode(PIN_2, OUTPUT); //出力モード
	pinMode(PIN_3, OUTPUT); //出力モード

	loop(); //ループさせたいプログラム
}