#include <stdint.h>
#include <stdlib.h>
#include <wiringPi.h>

#define pin_1 0 //０番ポート使用。ラズパイ１１番ピンに接続。
#define pin_2 3 //３番ポート使用。ラズパイ１５番ピンに接続。
#define pin_3 7 //７番ポート使用。ラズパイ７番ピンに接続。

int main(void)
{
	wiringPiSetup();		//https://projects.drogon.net/raspberry-pi/wiringpi/pins/を参照してポート番号を照らし合わせる。
	pinMode(pin_1, OUTPUT); //出力モード
	pinMode(pin_2, OUTPUT); //出力モード
	pinMode(pin_3, OUTPUT); //出力モード

	for (;;) //繰り返し処理
	{
		digitalWrite(pin_1, HIGH); //+３.３Vをオン
		delay(500);				   //()秒間オンにしたままにする。(ミリ秒)
		digitalWrite(pin_1, LOW);  //+３.３Vをオフ。つまり、０V
		digitalWrite(pin_2, HIGH); //+３.３Vをオン
		delay(500);				   //()秒間オンにしたままにする。(ミリ秒)
		digitalWrite(pin_2, LOW);  //+３.３Vをオフ。つまり、０V
		digitalWrite(pin_3, HIGH); //+３.３Vをオン
		delay(500);				   //()秒間オンにしたままにする。(ミリ秒)
		digitalWrite(pin_3, LOW);  //+３.３Vをオフ。つまり、０V
	}

	return 0;
}