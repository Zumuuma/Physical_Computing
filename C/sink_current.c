#include <stdint.h>
#include <stdlib.h>
#include <wiringPi.h>

#define pin 7 //7番ポート使用

int main(void)
{
	wiringPiSetup();	  //https://projects.drogon.net/raspberry-pi/wiringpi/pins/を参照してポート番号を照らし合わせる。
	pinMode(pin, OUTPUT); //出力モード
	for (;;)			  //ループ処理
	{
		digitalWrite(pin, LOW);	 //+3.3Vをオフ。つまり、オン状態にする。
		delay(1000);			 //()秒間オフにしたままにする。
		digitalWrite(pin, HIGH); //+3.3Vをオン。つまり、オフ状態にする。
		delay(1000);			 //()秒間オンにしたままにする。
	}

	return 0;
}
