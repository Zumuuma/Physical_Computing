#include <stdint.h>
#include <stdlib.h>
#include <wiringPi.h>

#define pin 7 //#7�ԃ|�[�g�g�p

int main(void)
{
	wiringPiSetup();	  //https://projects.drogon.net/raspberry-pi/wiringpi/pins/���Q�Ƃ��ă|�[�g�ԍ����Ƃ炵���킹��B
	pinMode(pin, OUTPUT); //�o�̓��[�h
	for (;;)			  //���[�v����
	{
		digitalWrite(pin, HIGH); //+3.3V���I��
		delay(1000);			 //()�b�ԃI���ɂ����܂܂ɂ���B
		digitalWrite(pin, LOW);	 //+3.3V���I�t�B�܂�A0V
		delay(1000);			 //()�b�ԃI�t�ɂ����܂܂ɂ���B
	}

	return 0;
}