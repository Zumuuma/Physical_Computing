#include <stdint.h>
#include <stdlib.h>
#include <wiringPi.h>

#define GPIO0 0 //�O�ԃ|�[�g�g�p�B���Y�p�C�P�P�ԃs���ɐڑ��B
#define GPIO1 1 //�P�ԃ|�[�g�g�p�B���Y�p�C�P�Q�ԃs���ɐڑ��B
#define GPIO2 2 //�Q�ԃ|�[�g�g�p�B���Y�p�C�P�R�ԃs���ɐڑ��B
#define GPIO3 3 //�R�ԃ|�[�g�g�p�B���Y�p�C�P�T�ԃs���ɐڑ��B
#define GPIO4 4 //�S�ԃ|�[�g�g�p�B���Y�p�C�P�U�ԃs���ɐڑ��B
#define GPIO5 5 //�T�ԃ|�[�g�g�p�B���Y�p�C�P�W�ԃs���ɐڑ��B
#define GPIO6 6 //�U�ԃ|�[�g�g�p�B���Y�p�C�Q�Q�ԃs���ɐڑ��B
#define GPIO7 7 //�V�ԃ|�[�g�g�p�B���Y�p�C�V�ԃs���ɐڑ��B

int main(void)
{
	wiringPiSetup();		//https://projects.drogon.net/raspberry-pi/wiringpi/pins/���Q�Ƃ��ă|�[�g�ԍ����Ƃ炵���킹��B
	pinMode(GPIO0, OUTPUT); //�o�̓��[�h
	pinMode(GPIO1, OUTPUT); //�o�̓��[�h
	pinMode(GPIO2, OUTPUT); //�o�̓��[�h
	pinMode(GPIO3, OUTPUT); //�o�̓��[�h
	pinMode(GPIO4, OUTPUT); //�o�̓��[�h
	pinMode(GPIO5, OUTPUT); //�o�̓��[�h
	pinMode(GPIO6, OUTPUT); //�o�̓��[�h
	pinMode(GPIO7, OUTPUT); //�o�̓��[�h

	digitalWrite(GPIO0, LOW); //+�R.�RV���I�t�B�܂�A�OV
	digitalWrite(GPIO1, LOW); //+�R.�RV���I�t�B�܂�A�OV
	digitalWrite(GPIO2, LOW); //+�R.�RV���I�t�B�܂�A�OV
	digitalWrite(GPIO3, LOW); //+�R.�RV���I�t�B�܂�A�OV
	digitalWrite(GPIO4, LOW); //+�R.�RV���I�t�B�܂�A�OV
	digitalWrite(GPIO5, LOW); //+�R.�RV���I�t�B�܂�A�OV
	digitalWrite(GPIO6, LOW); //+�R.�RV���I�t�B�܂�A�OV
	digitalWrite(GPIO7, LOW); //+�R.�RV���I�t�B�܂�A�OV

	return 0;
}