/*
 ============================================================================
 Name        : passive_buzzer.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <softTone.h>

#define buzzer 26

int octval[22]={0,131,147,165,196,220,247,262,294,330,
	        350,392,440,494,524,588,659,699,784,880,988};

int main(void)
{
	puts("!!!Hello buzzer"); /* prints !!!Hello World!!! */

	if(wiringPiSetup() == -1)
	{
		  puts("wiringPiSetup() is failed :\n");
		  return 1;
	}

	 pinMode(buzzer, OUTPUT);
	 softToneCreate(buzzer);

	for(;;)
	{
         int i;
         for(i=0;i<10;i++)
	  {
            softToneWrite(buzzer,octval[i]);
            delay(500);
	  }

         for(i=100;i<400;i=i+10)
	  {
            softToneWrite(buzzer,i);
            delay(10);
	  }
         break;
	}

	return EXIT_SUCCESS;
}
