#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define PWM_PIN 1	 //�P�ԃ|�[�g�g�p�B���Y�p�C�P�Q�ԃs���ɐڑ��B
#define LIGHT_UP 7	 //�V�ԃ|�[�g�g�p�B���Y�p�C�V�ԃs���ɐڑ��B
#define LIGHT_DOWN 3 //�R�ԃ|�[�g�g�p�B���Y�p�C�P�T�ԃs���ɐڑ�

int light_up_val = 0;		//���C�g�A�b�v�������ꂽ���̏��
int light_down_val = 0;		//���C�g�_�E���������ꂽ���̏��
int old_light_up_val = 0;	//���C�g�A�b�v�̌Â���ԕۊ�
int old_light_down_val = 0; //���C�g�_�E���̌Â���ԕۊ�

void loop()
{
	int duty_rate = 0; //�f���[�e�B�[��
	for (;;)
	{
		light_up_val = digitalRead(LIGHT_UP);	  //���͂�ǂ�light_up_val�ɐV�N�Ȓl��ۑ�
		light_down_val = digitalRead(LIGHT_DOWN); //���͂�ǂ�light_down_val�ɐV�N�Ȓl��ۑ�

		if ((light_up_val == HIGH) && (old_light_up_val == LOW)) //���C�g�A�b�v�{�^���������ꂽ���̏���
		{
			duty_rate += 200; //�f���[�e�B�[����グ��
			delay(200);		  //�f�o�E���V���O����
		}

		old_light_up_val = light_up_val; //�O�̏�ԕۊ�

		if ((light_down_val == HIGH) && (old_light_down_val == LOW)) //���C�g�_�E���{�^���������ꂽ���̏���
		{
			duty_rate -= 200; //�f���[�e�B�[���������
			delay(200);		  //�f�o�E���V���O����
		}

		if (duty_rate >= 2000) //�f���[�e�B�[�䂪�Q�O�O�O��������duty_rate�ɂQ�O�O�O��������B
		{
			duty_rate = 2000;
		}
		else if (duty_rate <= 0) //�f���[�e�B�[�䂪�O��������duty_rate�ɂO��������B
		{
			duty_rate = 0;
		}

		old_light_down_val = light_down_val; //�O�̏�ԕۊ�

		pwmWrite(PWM_PIN, duty_rate); //pwmWrite(pin�ԍ�,�f���[�e�B�[��(�O�`pwm range�͈̔�)) (��F�W�O��(�P�U�O�O/�Q�O�O�O))
	}
}

int main(void)
{
	wiringPiSetup();			  //https://projects.drogon.net/raspberry-pi/wiringpi/pins/���Q�Ƃ��ă|�[�g�ԍ����Ƃ炵���킹��B
	pinMode(LIGHT_UP, INPUT);	  //LIGHT_UP�͓��͂ɐݒ�
	pinMode(LIGHT_DOWN, INPUT);	  //LIGHT_DOWN�͓��͂ɐݒ�
	pinMode(PWM_PIN, PWM_OUTPUT); //PWM�Ή��s����PWM�o�͂ɐݒ�
	pwmSetMode(PWM_MODE_MS);	  //PWM�̃��[�h�w��
	//PWM���g�� �� �P�X.�QMHz / (CLOCK�l �� RANGE�l)�@(��F�P�X,�Q�O�O,�O�O�O / (�Q,�O�O�O * �X�U) = �P�O�O (Hz))
	pwmSetClock(96);   //CLOCK�l
	pwmSetRange(2000); //RANGE�l

	loop(); //���[�v���������v���O����

	return 0;
}