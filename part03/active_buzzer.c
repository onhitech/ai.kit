/*
 ============================================================================
 Name        : active_buzzer.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define buzzer 26

int main(void) 
{
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	if(wiringPiSetup() == -1)
	{
		  puts("wiringPiSetup() is failed :\n");
		  return 1;
	}

	 pinMode(buzzer, OUTPUT);

	for(;;)
	{
         int i;
         for(i=0;i<8;i++)
	  { 
	    printf("buzzer short %d \n",i);
            digitalWrite(buzzer,1);
            delay(300);	    
            digitalWrite(buzzer,0);
            delay(300);	    
	  }
        
	 for(i=0;i<8;i++)
	  { 
	    printf("buzzer short %d \n",i);
            digitalWrite(buzzer,1);
            delay(600);	    
            digitalWrite(buzzer,0);
            delay(600);	    
	  }
         break;
	}
	
	return EXIT_SUCCESS;
}
