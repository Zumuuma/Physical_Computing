#include <stdint.h>
#include <stdlib.h>
#include <wiringPi.h>

#define pin_1 0 //�O�ԃ|�[�g�g�p�B���Y�p�C�P�P�ԃs���ɐڑ��B
#define pin_2 3 //�R�ԃ|�[�g�g�p�B���Y�p�C�P�T�ԃs���ɐڑ��B
#define pin_3 7 //�V�ԃ|�[�g�g�p�B���Y�p�C�V�ԃs���ɐڑ��B

int main(void)
{
	wiringPiSetup();		//https://projects.drogon.net/raspberry-pi/wiringpi/pins/���Q�Ƃ��ă|�[�g�ԍ����Ƃ炵���킹��B
	pinMode(pin_1, OUTPUT); //�o�̓��[�h
	pinMode(pin_2, OUTPUT); //�o�̓��[�h
	pinMode(pin_3, OUTPUT); //�o�̓��[�h

	for (;;) //�J��Ԃ�����
	{
		digitalWrite(pin_1, HIGH); //+�R.�RV���I��
		delay(500);				   //()�b�ԃI���ɂ����܂܂ɂ���B(�~���b)
		digitalWrite(pin_1, LOW);  //+�R.�RV���I�t�B�܂�A�OV
		digitalWrite(pin_2, HIGH); //+�R.�RV���I��
		delay(500);				   //()�b�ԃI���ɂ����܂܂ɂ���B(�~���b)
		digitalWrite(pin_2, LOW);  //+�R.�RV���I�t�B�܂�A�OV
		digitalWrite(pin_3, HIGH); //+�R.�RV���I��
		delay(500);				   //()�b�ԃI���ɂ����܂܂ɂ���B(�~���b)
		digitalWrite(pin_3, LOW);  //+�R.�RV���I�t�B�܂�A�OV
	}

	return 0;
}