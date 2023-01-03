/*
 ============================================================================
 Name        : servo_motor.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <errno.h>

#define SERVO 1

#define uint8_t unsigned char
#define uint16_t unsigned int

int main(void) 
{
	printf("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	if(wiringPiSetup() == -1)
	{
	  puts("wiringPiSetup() is failed :\n");
	  return 1;
	}

 pinMode(SERVO,1);

 softPwmCreate(SERVO,0,100);

 uint8_t i;

 for(i=0;i<3;i++)
 {
 softPwmWrite(SERVO,1);
 printf("pos 1 180 deg \n");
 delay(1000);

 softPwmWrite(SERVO,10);
 printf("pos 10 90 deg \n");
 delay(1000);
 
 softPwmWrite(SERVO,19);
 printf("pos 1 19 -180 deg \n");
 delay(1000);
 }

return EXIT_SUCCESS;
}
