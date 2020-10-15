#include <stdint.h>
#include <stdlib.h>
#include <wiringPi.h>

#define GPIO0 0 //０番ポート使用。ラズパイ１１番ピンに接続。
#define GPIO1 1 //１番ポート使用。ラズパイ１２番ピンに接続。
#define GPIO2 2 //２番ポート使用。ラズパイ１３番ピンに接続。
#define GPIO3 3 //３番ポート使用。ラズパイ１５番ピンに接続。
#define GPIO4 4 //４番ポート使用。ラズパイ１６番ピンに接続。
#define GPIO5 5 //５番ポート使用。ラズパイ１８番ピンに接続。
#define GPIO6 6 //６番ポート使用。ラズパイ２２番ピンに接続。
#define GPIO7 7 //７番ポート使用。ラズパイ７番ピンに接続。

int main(void)
{
	wiringPiSetup();		//https://projects.drogon.net/raspberry-pi/wiringpi/pins/を参照してポート番号を照らし合わせる。
	pinMode(GPIO0, OUTPUT); //出力モード
	pinMode(GPIO1, OUTPUT); //出力モード
	pinMode(GPIO2, OUTPUT); //出力モード
	pinMode(GPIO3, OUTPUT); //出力モード
	pinMode(GPIO4, OUTPUT); //出力モード
	pinMode(GPIO5, OUTPUT); //出力モード
	pinMode(GPIO6, OUTPUT); //出力モード
	pinMode(GPIO7, OUTPUT); //出力モード

	digitalWrite(GPIO0, LOW); //+３.３Vをオフ。つまり、０V
	digitalWrite(GPIO1, LOW); //+３.３Vをオフ。つまり、０V
	digitalWrite(GPIO2, LOW); //+３.３Vをオフ。つまり、０V
	digitalWrite(GPIO3, LOW); //+３.３Vをオフ。つまり、０V
	digitalWrite(GPIO4, LOW); //+３.３Vをオフ。つまり、０V
	digitalWrite(GPIO5, LOW); //+３.３Vをオフ。つまり、０V
	digitalWrite(GPIO6, LOW); //+３.３Vをオフ。つまり、０V
	digitalWrite(GPIO7, LOW); //+３.３Vをオフ。つまり、０V

	return 0;
}