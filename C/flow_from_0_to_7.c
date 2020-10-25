#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define PIN_1 0 //０番ポート使用。ラズパイ１１番ピンに接続。
#define PIN_2 3 //３番ポート使用。ラズパイ１５番ピンに接続。
#define PIN_3 7 //７番ポート使用。ラズパイ７番ピンに接続。

int data[3] = {0}; //ここに保存。０で初期化
int x = 0;		   //変換したい１０進数

int convert_from_10_to_2(void) //１０進数から２進数に変換する関数
{
	int z = x;	 //変換したい１０進数
	int tmp = 0; //余りを代入する変数。０で初期化

	for (int i = 0; i < 3; i++)
	{
		tmp = z % 2;   //余りを求めてtmpに代入
		z = z / 2;	   //変換したい１０進数を２で割る
		data[i] = tmp; //２進数を保存するところに余り(tmp)を代入
	}

	printf("%d %d %d\n", data[2], data[1], data[0]); //コマンドプロンプト上で値を表示

	return 0;
}

int main(void)
{
	wiringPiSetup();		//https://projects.drogon.net/raspberry-pi/wiringpi/pins/を参照してポート番号を照らし合わせる。
	pinMode(PIN_1, OUTPUT); //出力モード
	pinMode(PIN_2, OUTPUT); //出力モード
	pinMode(PIN_3, OUTPUT); //出力モード

	for (;;)
	{
		convert_from_10_to_2();

		if (data[2] == 1)
		{
			digitalWrite(PIN_1, HIGH); //+３.３Vをオン
		}
		else
		{
			digitalWrite(PIN_1, LOW); //+３.３Vをオフ。つまり、０V
		}

		if (data[1] == 1)
		{
			digitalWrite(PIN_2, HIGH); //+３.３Vをオン
		}
		else
		{
			digitalWrite(PIN_2, LOW); //+３.３Vをオフ。つまり、０V
		}

		if (data[0] == 1)
		{
			digitalWrite(PIN_3, HIGH); //+３.３Vをオン
		}
		else
		{
			digitalWrite(PIN_3, LOW); //+３.３Vをオフ。つまり、０V
		}

		delay(500); //xの値をインクリメントするまでの時間(ミリ秒)

		x = x + 1; //xの値をインクリメント

		if (x == 8) //xの値が８ならxの値を０に戻す
		{
			x = 0;
		}
	}

	return 0;
}
