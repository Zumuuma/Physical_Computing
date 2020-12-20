#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

const int LED = 2;	  //２番ポート使用。ラズパイ１３番ピンに接続。
const int BUTTON = 0; //０番ポート使用。ラズパイ１１番ピンに接続。

int val = 0;	 //入力ピンの状態がこの変数(val)に記憶される
int old_val = 0; //valの前の値を保存しておく変数
int state = 0;	 //LEDの状態(0ならオフ、1ならオン)

void loop()
{
	for (;;)
	{
		val = digitalRead(BUTTON); //入力を読みvalに新鮮な値を保存

		//変化があるかどうかチェック
		if ((val == HIGH) && (old_val == LOW))
		{
			state = 1 - state;
			delay(200);
		}

		old_val = val; //valはもう古くなったので、保管しておく

		if (state == 1)
		{
			digitalWrite(LED, HIGH); //LEDオン
		}
		else
		{
			digitalWrite(LED, LOW); //LEDオフ
		}
	}
}

int main(void)
{
	wiringPiSetup();		//https://projects.drogon.net/raspberry-pi/wiringpi/pins/を参照してポート番号を照らし合わせる。
	pinMode(LED, OUTPUT);	//Raspberry PiにLEDが出力であると伝える
	pinMode(BUTTON, INPUT); //BUTTONは入力に設定

	loop();
}