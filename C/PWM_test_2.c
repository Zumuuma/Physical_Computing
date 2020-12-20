#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define PWM_PIN 1 //１番ポート使用。ラズパイ１２番ピンに接続。

void loop()
{
	int duty_rate = 0; //デューティー比
	for (;;)
	{
		pwmWrite(PWM_PIN, duty_rate); //pwmWrite(pin番号,デューティー比(０～pwm rangeの範囲)) (例：８０％(１６００/２０００))
		duty_rate += 100;			  //デューティー比を１００づつ(５％づつ)増やしていく
		delay(100);
		if (duty_rate >= 2000) //デューティー比が２０００(つまり１００％)になったら０に戻す
		{
			duty_rate = 0;
		}
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