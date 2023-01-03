/*
 ============================================================================
 Name        : step_motor.c
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
#include <wiringPiI2C.h>

#define uint8_t unsigned char
#define uint16_t unsigned int

#define speed 2
#define stop -99

int cw=1, ccw=-1;
//int phase[5][4] ={{1,1,0,0},{0,1,1,0},{0,0,1,1},{1,0,0,1},{0,0,0,0}};

unsigned char step[5] ={0x0c, 0x06, 0x03, 0x09, 0x00};

int fd;

void run( int i)
{
    unsigned char ph;
    if(i==stop)ph=4;
    else
    {
       if(i>=0)ph=i%4;
    }
	 wiringPiI2CWriteReg8(fd, 0x03, step[ph]);

	 return;
}

void run_angle(int angle, int dir)
{
    int duration;
    
    duration = (int)(angle*5.72);

    if(dir==cw)
    {
      for(int i=0;i<duration;i++)
      {
	   run(i);
	   delay(speed);
      }   
    }
    else if(dir==ccw)
    {

      for(int i=duration; i>0; i--)
      {
           run(i);	   
	   delay(speed);
      }   
    } 
	 return;
}

void run_cycle(int times, int dir)
{
   for(int i=0;i<times;i++)run_angle(360,dir);

   return;
}

int main(void)
{
	unsigned int i=0;
	unsigned char ph=0;

	puts("step motor!!!"); /* prints !!!Hello World!!! */

	if(wiringPiSetup() == -1)
	{
	  puts("wiringPiSetup() is failed :\n");
	  return 1;
	}

        if((fd = wiringPiI2CSetup(0x21))<0)
	{
		  puts("wiringPiI2CSetup failed:\n");
        }

       if(wiringPiI2CWriteReg8(fd, 0x06, 0) == -1)
       {
		  puts("write failed...\n");
		 }

       if(wiringPiI2CWriteReg8(fd, 0x07, 0) == -1)
       {
			  puts("write failed...\n");
       }
       
       run_angle(90,cw);
       delay(1000);
       
       run_angle(180,ccw);
       delay(1000);

       run_cycle(2,cw);
       run(stop);

return EXIT_SUCCESS;
}
