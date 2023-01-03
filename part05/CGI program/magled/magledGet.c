//=======================================
// magledGet.c CGI
//	LED controlled by Magnetic SW (GET)
//=======================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wiringPi.h>		////

#define P_LED	1		//// BCM_GPIO #18
#define P_MAG	4		//// BCM_GPIO #24

int main(void) {
	int btn;

	if(wiringPiSetup() == -1)		//// wiringPi pin #
		return 1;

	pinMode(P_LED, OUTPUT);			////
	pinMode(P_MAG, INPUT);			////

	printf("Content-type: text/html\n\n");

	printf("<html>\n\n");
	printf("<head>\n");
	printf("<title>LED Controlled by Magnetic (GET)</title>\n");
	printf("</head>\n\n");
	printf("<body>\n");
	printf("<h1>LED Controlled by Magnetic (GET)</h1>\n");
	printf("<hr><p>\n");

	// LED controlled by Magnetic...
	btn = digitalRead(P_MAG);
	if(btn == 1) {
		digitalWrite(P_LED, HIGH);
		printf("Magnetic ON ==> LED ON!!!<br>");
	}
	else {
		digitalWrite(P_LED, LOW);
		printf("Magnetic OFF ==> LED OFF!!!<br>");
	}

	printf("</body>\n\n");
	printf("</html>\n");

	return 0;
}

