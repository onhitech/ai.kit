/*
 ============================================================================
 Name        : ultra.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <wiringPi.h>

#define uint8_t unsigned char
#define uint16_t unsigned int

int TRIG =2;
int ECHO =3;

static int Echo_Test(void)
{
 unsigned long tx_time=0;
 unsigned long rx_time=0;
 float distance =0;
 unsigned long timeout=5000000;
 unsigned long wait_time=micros();

 pinMode(TRIG,OUTPUT);
 pinMode(ECHO,INPUT);

 digitalWrite(TRIG,0);
 delay(500);
 digitalWrite(TRIG,1);
 delayMicroseconds(10);
 digitalWrite(TRIG,0);

 while((digitalRead(ECHO)==0) && ((micros()-wait_time)<timeout))
 {
   if(digitalRead(ECHO)==1)break;
 }

  if((micros()-wait_time)>timeout)
  {
    printf("0 out of range_micros=%d wait-time=%d \n", micros(), wait_time);
  }
 
  tx_time=micros();

 while((digitalRead(ECHO)==1) && ((micros()-wait_time)<timeout))
 {
   if(digitalRead(ECHO)==0)break;
 }

  if((micros()-wait_time)>timeout)
  {
    printf("1 out of range.\n");
  }
 
  rx_time=micros();
  distance=(float)(rx_time-tx_time)*0.017;
  printf("distance %.2f cm\n",distance);
  return 1;
}

int main(void)
{
	puts("HC-SR04 distance measure\n"); /* prints !!!Hello World!!! */

	if(wiringPiSetup() == -1)
	{
	  puts("wiringPiSetup() is failed :\n");
	  return 1;
	}
     
	for(int i=0;;i++)
	{
	 Echo_Test();
	 sleep(1);
	 printf("loop=%d",i);
        }

	return EXIT_SUCCESS;
}
