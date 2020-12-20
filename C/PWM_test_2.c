#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define PWM_PIN 1 //�P�ԃ|�[�g�g�p�B���Y�p�C�P�Q�ԃs���ɐڑ��B

void loop()
{
	int duty_rate = 0; //�f���[�e�B�[��
	for (;;)
	{
		pwmWrite(PWM_PIN, duty_rate); //pwmWrite(pin�ԍ�,�f���[�e�B�[��(�O�`pwm range�͈̔�)) (��F�W�O��(�P�U�O�O/�Q�O�O�O))
		duty_rate += 100;			  //�f���[�e�B�[����P�O�O�Â�(�T���Â�)���₵�Ă���
		delay(100);
		if (duty_rate >= 2000) //�f���[�e�B�[�䂪�Q�O�O�O(�܂�P�O�O��)�ɂȂ�����O�ɖ߂�
		{
			duty_rate = 0;
		}
	}
}

int main(void)
{
	wiringPiSetup(); //https://projects.drogon.net/raspberry-pi/wiringpi/pins/���Q�Ƃ��ă|�[�g�ԍ����Ƃ炵���킹��B
	pinMode(PWM_PIN, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	//PWM���g�� �� �P�X.�QMHz / (CLOCK�l �� RANGE�l)�@(��F�P�X,�Q�O�O,�O�O�O / (�Q,�O�O�O * �X�U) = �P�O�O (Hz))
	pwmSetClock(96);   //CLOCK�l
	pwmSetRange(2000); //RANGE�l

	loop();

	return 0;
}