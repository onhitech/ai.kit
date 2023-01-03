//=======================================
// motion_01.c
//	LED ON while detecting motion
//=======================================
#include <stdio.h>
#include <wiringPi.h>

#define P_LED_G		27		// BCM_GPIO #16
#define P_MOT	    0		// BCM_GPIO #17

int main(void) {
	int status;

	printf("[LED/MOT testing....]\n");

	if(wiringPiSetup() == -1)
		return 1;

	pinMode(P_LED_G, OUTPUT);
	pinMode(P_MOT, INPUT);

	printf("P_LED_Green ON while P_MOT ON.........\n");

	status = 0;
	while(1) {
		status = digitalRead(P_MOT);
		if(status==1) {
			digitalWrite(P_LED_G, HIGH);
			printf("ON.........\n");
		}
		else {
			digitalWrite(P_LED_G, LOW);
			printf("OFF.........\n");
		}
		delay(500);
	}

	return 0;
}


