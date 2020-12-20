#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define PWM_PIN 1	 //１番ポート使用。ラズパイ１２番ピンに接続。
#define LIGHT_UP 7	 //７番ポート使用。ラズパイ７番ピンに接続。
#define LIGHT_DOWN 3 //３番ポート使用。ラズパイ１５番ピンに接続

int light_up_val = 0;		//ライトアップを押された時の状態
int light_down_val = 0;		//ライトダウンを押された時の状態
int old_light_up_val = 0;	//ライトアップの古い状態保管
int old_light_down_val = 0; //ライトダウンの古い状態保管

void loop()
{
	int duty_rate = 0; //デューティー比
	for (;;)
	{
		light_up_val = digitalRead(LIGHT_UP);	  //入力を読みlight_up_valに新鮮な値を保存
		light_down_val = digitalRead(LIGHT_DOWN); //入力を読みlight_down_valに新鮮な値を保存

		if ((light_up_val == HIGH) && (old_light_up_val == LOW)) //ライトアップボタンが押された時の処理
		{
			duty_rate += 200; //デューティー比を上げる
			delay(200);		  //デバウンシング処理
		}

		old_light_up_val = light_up_val; //前の状態保管

		if ((light_down_val == HIGH) && (old_light_down_val == LOW)) //ライトダウンボタンが押された時の処理
		{
			duty_rate -= 200; //デューティー比を下げる
			delay(200);		  //デバウンシング処理
		}

		if (duty_rate >= 2000) //デューティー比が２０００超えたらduty_rateに２０００を代入する。
		{
			duty_rate = 2000;
		}
		else if (duty_rate <= 0) //デューティー比が０超えたらduty_rateに０を代入する。
		{
			duty_rate = 0;
		}

		old_light_down_val = light_down_val; //前の状態保管

		pwmWrite(PWM_PIN, duty_rate); //pwmWrite(pin番号,デューティー比(０～pwm rangeの範囲)) (例：８０％(１６００/２０００))
	}
}

int main(void)
{
	wiringPiSetup();			  //https://projects.drogon.net/raspberry-pi/wiringpi/pins/を参照してポート番号を照らし合わせる。
	pinMode(LIGHT_UP, INPUT);	  //LIGHT_UPは入力に設定
	pinMode(LIGHT_DOWN, INPUT);	  //LIGHT_DOWNは入力に設定
	pinMode(PWM_PIN, PWM_OUTPUT); //PWM対応ピンはPWM出力に設定
	pwmSetMode(PWM_MODE_MS);	  //PWMのモード指定
	//PWM周波数 ＝ １９.２MHz / (CLOCK値 ＊ RANGE値)　(例：１９,２００,０００ / (２,０００ * ９６) = １００ (Hz))
	pwmSetClock(96);   //CLOCK値
	pwmSetRange(2000); //RANGE値

	loop(); //ループさせたいプログラム

	return 0;
}