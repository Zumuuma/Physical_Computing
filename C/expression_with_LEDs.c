#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define pin_1 0 //�O�ԃ|�[�g�g�p�B���Y�p�C�P�P�ԃs���ɐڑ��B
#define pin_2 3 //�R�ԃ|�[�g�g�p�B���Y�p�C�P�T�ԃs���ɐڑ��B
#define pin_3 7 //�V�ԃ|�[�g�g�p�B���Y�p�C�V�ԃs���ɐڑ��B

int data[3] = {0}; //�Q�i����ۑ��B�O�ŏ�����

int convert_from_10_to_20(void) //�P�O�i������Q�i���ɕϊ�����֐�
{
	int x = 5;	 //�ϊ��������P�O�i��
	int tmp = 0; //�]���������ϐ��B�O�ŏ�����

	for (int i = 0; i < 3; i++)
	{
		tmp = x % 2;   //�]������߂�tmp�ɑ��
		x = x / 2;	   //�ϊ��������P�O�i�����Q�Ŋ���
		data[i] = tmp; //�Q�i����ۑ�����Ƃ���ɗ]��(tmp)����
	}

	printf("%d %d %d\n", data[2], data[1], data[0]); //�R�}���h�v�����v�g��Œl��\��

	return 0;
}

int main(void)
{
	wiringPiSetup();		//https://projects.drogon.net/raspberry-pi/wiringpi/pins/���Q�Ƃ��ă|�[�g�ԍ����Ƃ炵���킹��B
	pinMode(pin_1, OUTPUT); //�o�̓��[�h
	pinMode(pin_2, OUTPUT); //�o�̓��[�h
	pinMode(pin_3, OUTPUT); //�o�̓��[�h

	convert_from_10_to_20();

	if (data[2] == 1)
	{
		digitalWrite(pin_1, HIGH); //+�R.�RV���I��
	}
	else
	{
		digitalWrite(pin_1, LOW); //+�R.�RV���I�t�B�܂�A�OV
	}

	if (data[1] == 1)
	{
		digitalWrite(pin_2, HIGH); //+�R.�RV���I��
	}
	else
	{
		digitalWrite(pin_2, LOW); //+�R.�RV���I�t�B�܂�A�OV
	}

	if (data[0] == 1)
	{
		digitalWrite(pin_3, HIGH); //+�R.�RV���I��
	}
	else
	{
		digitalWrite(pin_3, LOW); //+�R.�RV���I�t�B�܂�A�OV
	}

	return 0;
}