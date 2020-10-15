#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define pin 7 //７番ポート使用。ラズパイ７番ピンに接続。

int main(void)
{
	wiringPiSetup();	  //https://projects.drogon.net/raspberry-pi/wiringpi/pins/を参照してポート番号を照らし合わせる。
	pinMode(pin, OUTPUT); //出力モード

	for (;;) //ループ処理
	{
		digitalWrite(pin, HIGH); //+３.３Vをオン
		delay(1000);			 //()秒間オンにしたままにする。(ミリ秒)
		digitalWrite(pin, LOW);	 //+３.３Vをオフ。つまり、０V
		delay(1000);			 //()秒間オフにしたままにする。(ミリ秒)
	}

	return 0;
}