/*
 ============================================================================
 Name        : dc_motor.c
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

#define foreward 25
#define backward 24

#define uint8_t unsigned char
#define uint16_t unsigned int

void fore_run(int duty)
{
	softPwmWrite(foreward,duty);
	softPwmWrite(backward,0);
	return;
}

void back_run(int duty)
{
	softPwmWrite(foreward,0);
	softPwmWrite(backward,duty);
	return;
}

void motor_stop()
{
softPwmWrite(foreward,0);
softPwmWrite(backward,0);

digitalWrite(foreward,0);
digitalWrite(backward,0);
}

int main(void)
{

 uint8_t i;

 printf("!!!Hello World!!!"); /* prints !!!Hello World!!! */

 if(wiringPiSetup() == -1)
	{
	  puts("wiringPiSetup() is failed :\n");
	  return 1;
	}

	pinMode(foreward,OUTPUT);
	pinMode(backward,OUTPUT);

 softPwmCreate(foreward,50,100);
 softPwmCreate(backward,50,100);


 for(i=2;i<5;i++)
 {
    printf("pwm run =%d /%% duty_cycle \n", i*10);
    printf("foreward run \n" );
    fore_run(i*10);

    delay(1000);
   
    printf("backward run \n" );
    back_run(i*10);
    
    delay(1000);
  
    motor_stop();
    printf("--------\n");
 }

 delay(1000);
 motor_stop();

 return EXIT_SUCCESS;
}
