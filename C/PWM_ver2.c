#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define PWM_PIN 1 //�P�ԃ|�[�g�g�p�B���Y�p�C�P�Q�ԃs���ɐڑ��B

void loop()
{
	for (;;)
	{
		pwmWrite(PWM_PIN, 1600); //pwmWrite(pin�ԍ�,�f���[�e�B�[��(�O�`pwm range�͈̔�)) (��F�W�O��(�P�U�O�O/�Q�O�O�O))
		delay(500);
		pwmWrite(PWM_PIN, 200); //pwmWrite(pin�ԍ�,�f���[�e�B�[��(�O�`pwm range�͈̔�)) (��F�P�O��(�Q�O�O/�Q�O�O�O))
		delay(500);
	}
}

int main(void)
{
	wiringPiSetup(); //https://projects.drogon.net/raspberry-pi/wiringpi/pins/���Q�Ƃ��ă|�[�g�ԍ����Ƃ炵���킹��B
	pinMode(PWM_PIN, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	//PWM���g�� �� �P�X.�QMHz / (CLOCK�l �� RANGE�l)�@(��F�P�X,�Q�O�O,�O�O�O / (�Q,�O�O�O * �X�U�O) = �P�O (Hz))
	pwmSetClock(960);  //CLOCK�l
	pwmSetRange(2000); //RANGE�l

	loop();

	return 0;
}