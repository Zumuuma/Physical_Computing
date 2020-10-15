#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define pin_1 0 //０番ポート使用。ラズパイ１１番ピンに接続。
#define pin_2 3 //３番ポート使用。ラズパイ１５番ピンに接続。
#define pin_3 7 //７番ポート使用。ラズパイ７番ピンに接続。

int data[3] = {0}; //２進数を保存。０で初期化

int convert_from_10_to_20(void) //１０進数から２進数に変換する関数
{
	int x = 5;	 //変換したい１０進数
	int tmp = 0; //余りを代入する変数。０で初期化

	for (int i = 0; i < 3; i++)
	{
		tmp = x % 2;   //余りを求めてtmpに代入
		x = x / 2;	   //変換したい１０進数を２で割る
		data[i] = tmp; //２進数を保存するところに余り(tmp)を代入
	}

	printf("%d %d %d\n", data[2], data[1], data[0]); //コマンドプロンプト上で値を表示

	return 0;
}

int main(void)
{
	wiringPiSetup();		//https://projects.drogon.net/raspberry-pi/wiringpi/pins/を参照してポート番号を照らし合わせる。
	pinMode(pin_1, OUTPUT); //出力モード
	pinMode(pin_2, OUTPUT); //出力モード
	pinMode(pin_3, OUTPUT); //出力モード

	convert_from_10_to_20();

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

	return 0;
}