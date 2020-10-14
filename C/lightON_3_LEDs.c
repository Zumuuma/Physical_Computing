#include <stdint.h>
#include <stdlib.h>
#include <wiringPi.h>

#define pin_1 0 //0番ポート使用。ラズパイ11番ピンに接続。
#define pin_2 3 //3番ポート使用。ラズパイ15番ピンに接続。
#define pin_3 7 //7番ポート使用。ラズパイ7番ピンに接続。

int main(void)
{
	wiringPiSetup();		//https://projects.drogon.net/raspberry-pi/wiringpi/pins/を参照してポート番号を照らし合わせる。
	pinMode(pin_1, OUTPUT); //出力モード
	pinMode(pin_2, OUTPUT); //出力モード
	pinMode(pin_3, OUTPUT); //出力モード
	for (;;)				//繰り返し処理
	{
		digitalWrite(pin_1, HIGH); //+3.3Vをオン
		delay(3000);			   //()秒間オンにしたままにする。
		digitalWrite(pin_1, LOW);  //+3.3Vをオフ。つまり、0V
		//delay(10);
		digitalWrite(pin_2, HIGH); //+3.3Vをオン
		delay(3000);			   //()秒間オンにしたままにする。
		digitalWrite(pin_2, LOW);  //+3.3Vをオフ。つまり、0V
		//delay(10);
		digitalWrite(pin_3, HIGH); //+3.3Vをオン
		delay(3000);			   //()秒間オンにしたままにする。
		digitalWrite(pin_3, LOW);  //+3.3Vをオフ。つまり、0V
								   //delay(10);
	}

	return 0;
}
