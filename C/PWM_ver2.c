#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define PWM_PIN 1 //‚P”Ôƒ|[ƒgg—pBƒ‰ƒYƒpƒC‚P‚Q”Ôƒsƒ“‚ÉÚ‘±B

void loop()
{
	for (;;)
	{
		pwmWrite(PWM_PIN, 1600); //pwmWrite(pin”Ô†,ƒfƒ…[ƒeƒB[”ä(‚O`pwm range‚Ì”ÍˆÍ)) (—áF‚W‚O“(‚P‚U‚O‚O/‚Q‚O‚O‚O))
		delay(500);
		pwmWrite(PWM_PIN, 200); //pwmWrite(pin”Ô†,ƒfƒ…[ƒeƒB[”ä(‚O`pwm range‚Ì”ÍˆÍ)) (—áF‚P‚O“(‚Q‚O‚O/‚Q‚O‚O‚O))
		delay(500);
	}
}

int main(void)
{
	wiringPiSetup(); //https://projects.drogon.net/raspberry-pi/wiringpi/pins/‚ğQÆ‚µ‚Äƒ|[ƒg”Ô†‚ğÆ‚ç‚µ‡‚í‚¹‚éB
	pinMode(PWM_PIN, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	//PWMü”g”  ‚P‚X.‚QMHz / (CLOCK’l – RANGE’l)@(—áF‚P‚X,‚Q‚O‚O,‚O‚O‚O / (‚Q,‚O‚O‚O * ‚X‚U‚O) = ‚P‚O (Hz))
	pwmSetClock(960);  //CLOCK’l
	pwmSetRange(2000); //RANGE’l

	loop();

	return 0;
}