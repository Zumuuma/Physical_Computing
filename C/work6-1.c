#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define PWM_PIN 1 //１番ポート使用。ラズパイ１２番ピンに接続。

void loop()
{
	for (;;)
	{
		pwmWrite(PWM_PIN, 1600); //pwmWrite(pin番号,デューティー比(０～pwm rangeの範囲)) (例：１０％(２００/２０００))
	}
}

int main(void)
{
	wiringPiSetup(); //https://projects.drogon.net/raspberry-pi/wiringpi/pins/を参照してポート番号を照らし合わせる。
	pinMode(PWM_PIN, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	//PWM周波数 ＝ １９.２MHz / (CLOCK値 ＊ RANGE値)　(例：１９,２００,０００ / (２,０００ * ９６) = １００ (Hz))
	pwmSetClock(96);   //CLOCK値
	pwmSetRange(2000); //RANGE値

	loop();

	return 0;
}