//=======================================
// rgbLed_01.c
//	led ON (Low signal)
//=======================================
#include <stdio.h>
#include <wiringPi.h>

#define P_LED_R		27		// BCM_GPIO #16
#define P_LED_G		28		// BCM_GPIO #20
#define P_LED_B		29		// BCM_GPIO #21

int main(void) {
	printf("[rgbLED testing....]\n");

	if(wiringPiSetup() == -1)
		return 1;

	pinMode(P_LED_R, OUTPUT);
	pinMode(P_LED_G, OUTPUT);
	pinMode(P_LED_B, OUTPUT);

	// all OFF
	digitalWrite(P_LED_R, HIGH);
	digitalWrite(P_LED_G, HIGH);
	digitalWrite(P_LED_B, HIGH);
	delay(3000);

	while(1) {
		printf("rLED ON.........\n");
		digitalWrite(P_LED_R, LOW);
		digitalWrite(P_LED_G, HIGH);
		digitalWrite(P_LED_B, HIGH);
		delay(2000);

		printf("gLED ON.........\n");
		digitalWrite(P_LED_R, HIGH);
		digitalWrite(P_LED_G, LOW);
		digitalWrite(P_LED_B, HIGH);
		delay(2000);

		printf("bLED ON.........\n");
		digitalWrite(P_LED_R, HIGH);
		digitalWrite(P_LED_G, HIGH);
		digitalWrite(P_LED_B, LOW);
		delay(2000);

		printf("(r+g)LED ON.........\n");
		digitalWrite(P_LED_R, LOW);
		digitalWrite(P_LED_G, LOW);
		digitalWrite(P_LED_B, HIGH);
		delay(2000);

		printf("(r+g+b)LED ON.........\n");
		digitalWrite(P_LED_R, LOW);
		digitalWrite(P_LED_G, LOW);
		digitalWrite(P_LED_B, LOW);
		delay(2000);

		printf("all LED OFF.........\n");
		digitalWrite(P_LED_R, HIGH);
		digitalWrite(P_LED_G, HIGH);
		digitalWrite(P_LED_B, HIGH);
		delay(4000);
	}

	return 0;
}


