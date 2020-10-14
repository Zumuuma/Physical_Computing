#include <stdint.h>
#include <stdlib.h>
#include <wiringPi.h>

#define pin_1 0 //0�ԃ|�[�g�g�p�B���Y�p�C11�ԃs���ɐڑ��B
#define pin_2 3 //3�ԃ|�[�g�g�p�B���Y�p�C15�ԃs���ɐڑ��B
#define pin_3 7 //7�ԃ|�[�g�g�p�B���Y�p�C7�ԃs���ɐڑ��B

int main(void)
{
	wiringPiSetup();		//https://projects.drogon.net/raspberry-pi/wiringpi/pins/���Q�Ƃ��ă|�[�g�ԍ����Ƃ炵���킹��B
	pinMode(pin_1, OUTPUT); //�o�̓��[�h
	pinMode(pin_2, OUTPUT); //�o�̓��[�h
	pinMode(pin_3, OUTPUT); //�o�̓��[�h
	for (;;)				//�J��Ԃ�����
	{
		digitalWrite(pin_1, HIGH); //+3.3V���I��
		delay(3000);			   //()�b�ԃI���ɂ����܂܂ɂ���B
		digitalWrite(pin_1, LOW);  //+3.3V���I�t�B�܂�A0V
		//delay(10);
		digitalWrite(pin_2, HIGH); //+3.3V���I��
		delay(3000);			   //()�b�ԃI���ɂ����܂܂ɂ���B
		digitalWrite(pin_2, LOW);  //+3.3V���I�t�B�܂�A0V
		//delay(10);
		digitalWrite(pin_3, HIGH); //+3.3V���I��
		delay(3000);			   //()�b�ԃI���ɂ����܂܂ɂ���B
		digitalWrite(pin_3, LOW);  //+3.3V���I�t�B�܂�A0V
								   //delay(10);
	}

	return 0;
}