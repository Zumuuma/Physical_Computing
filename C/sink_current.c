#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define pin 7 //�V�ԃ|�[�g�g�p�B���Y�p�C�V�ԃs���ɐڑ��B

int main(void)
{
	wiringPiSetup();	  //https://projects.drogon.net/raspberry-pi/wiringpi/pins/���Q�Ƃ��ă|�[�g�ԍ����Ƃ炵���킹��B
	pinMode(pin, OUTPUT); //�o�̓��[�h

	for (;;) //���[�v����
	{
		digitalWrite(pin, LOW);	 //+�R.�RV���I�t�B�܂�A�I����Ԃɂ���B
		delay(1000);			 //()�b�ԃI�t�ɂ����܂܂ɂ���B(�~���b)
		digitalWrite(pin, HIGH); //+�R.�RV���I���B�܂�A�I�t��Ԃɂ���B
		delay(1000);			 //()�b�ԃI���ɂ����܂܂ɂ���B(�~���b)
	}

	return 0;
}