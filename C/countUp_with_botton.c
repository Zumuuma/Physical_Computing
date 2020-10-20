#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define pin_3 0	 //０番ポート使用。ラズパイ１１番ピンに接続。
#define pin_2 2	 //２番ポート使用。ラズパイ１３番ピンに接続。
#define pin_1 3	 //３番ポート使用。ラズパイ１５番ピンに接続。
#define BUTTON 7 //７番ポート使用。ラズパイ７番ピンに接続。

int val = 0;	   //入力ピンの状態がこの変数(val)に記憶される
int old_val = 0;   //valの前の値を保存しておく変数
int data[3] = {0}; //ここに保存。０で初期化
int count = 0;	   //ボタンが押された回数を記憶

int convert_from_10_to_2(void) //１０進数から２進数に変換する関数
{
	int z = count; //変換したい１０進数
	int tmp = 0;   //余りを代入する変数。０で初期化

	for (int i = 0; i < 3; i++)
	{
		tmp = z % 2;   //余りを求めてtmpに代入
		z = z / 2;	   //変換したい１０進数を２で割る
		data[i] = tmp; //２進数を保存するところに余り(tmp)を代入
	}

	return 0;
}

void loop()
{
	for (;;)
	{
		val = digitalRead(BUTTON); //入力を読みvalに新鮮な値を保存

		if (val == HIGH) //ボタンが押されたら
		{
			count = 1 + count; //カウントアップする
			delay(200);		   //デバウンシング処理
		}

		old_val = val; //古いvalはここに保管(今回いらないかも)

		convert_from_10_to_2(); //１０進数から２進数に変換する関数

		if (data[2] == 1)
		{
			digitalWrite(pin_1, HIGH); //+３.３Vをオン
		}
		else
		{
			digitalWrite(pin_1, LOW); //+３.３Vをオフ。つまり、０V
		}

		if (data[1] == 1)
		{
			digitalWrite(pin_2, HIGH); //+３.３Vをオン
		}
		else
		{
			digitalWrite(pin_2, LOW); //+３.３Vをオフ。つまり、０V
		}

		if (data[0] == 1)
		{
			digitalWrite(pin_3, HIGH); //+３.３Vをオン
		}
		else
		{
			digitalWrite(pin_3, LOW); //+３.３Vをオフ。つまり、０V
		}

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
	pinMode(pin_1, OUTPUT); //出力モード
	pinMode(pin_2, OUTPUT); //出力モード
	pinMode(pin_3, OUTPUT); //出力モード

	loop(); //ループさせたいプログラム
}