#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define PIN_1 0 //０番ポート使用。ラズパイ１１番ピンに接続。
#define PIN_2 3 //３番ポート使用。ラズパイ１５番ピンに接続。
#define PIN_3 7 //７番ポート使用。ラズパイ７番ピンに接続。

int main(void)
{
	wiringPiSetup();		//https://projects.drogon.net/raspberry-pi/wiringpi/pins/を参照してポート番号を照らし合わせる。
	pinMode(PIN_1, OUTPUT); //出力モード
	pinMode(PIN_2, OUTPUT); //出力モード
	pinMode(PIN_3, OUTPUT); //出力モード

	for (;;) //繰り返し処理
	{
		digitalWrite(PIN_1, HIGH); //+３.３Vをオン
		delay(500);				   //()秒間オンにしたままにする。(ミリ秒)
		digitalWrite(PIN_1, LOW);  //+３.３Vをオフ。つまり、０V
		digitalWrite(PIN_2, HIGH); //+３.３Vをオン
		delay(500);				   //()秒間オンにしたままにする。(ミリ秒)
		digitalWrite(PIN_2, LOW);  //+３.３Vをオフ。つまり、０V
		digitalWrite(PIN_3, HIGH); //+３.３Vをオン
		delay(500);				   //()秒間オンにしたままにする。(ミリ秒)
		digitalWrite(PIN_3, LOW);  //+３.３Vをオフ。つまり、０V
	}

	return 0;
}
