//=======================================
// ledBtn_01.c
//	LED ON while press BTN
//=======================================
#include <stdio.h>
#include <wiringPi.h>

#define P_LED_G		27		// BCM_GPIO #16
#define P_LED_R		28		// BCM_GPIO #20
#define P_BTN_1	    4		// BCM_GPIO #23
#define P_BTN_2	    5		// BCM_GPIO #24

int main(void) {
	int btn_1;
	int btn_2;
	printf("[LED/BTN testing....]\n");

	if(wiringPiSetup() == -1)	// wiringPi pin #
		return 1;

	pinMode(P_LED_R, OUTPUT);
	pinMode(P_LED_G, OUTPUT);

	pinMode(P_BTN_1, INPUT);
    pinMode(P_BTN_2, INPUT);

	printf("P_LED ON while P_BTN press.........\n");

	btn = 0;
	while(1) {
		btn_1 = digitalRead(P_BTN_1);
		if(btn_1==1) {
			digitalWrite(P_LED_R, LOW);
			printf("LED_R_OFF.........\n");
		}
		else {
			digitalWrite(P_LED_R, HIGH);
			printf("LED_R_ON.........\n");
		}
		delay(2000);
		btn_2 = digitalRead(P_BTN_2);
		if(btn_2==1) {
			digitalWrite(P_LED_G, LOW);
			printf("LED_G_OFF.........\n");
		}
		else {
			digitalWrite(P_LED_G, HIGH);
			printf("LED_G_ON.........\n");
		}
		delay(2000);
	}

	return 0;
}


