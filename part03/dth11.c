/*
 ============================================================================
 Name        : dth11.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <wiringPi.h>

#define MAX_TIMINGS 85
#define dht 7

int data[5]={0,0,0,0,0};

void read_dht_data()
{
  uint8_t laststate =HIGH;
  uint8_t counter=0;
  uint8_t j=0,i;
  
  for(i=0;i<5;i++) data[i]=0;

  pinMode(dht, OUTPUT);
  digitalWrite(dht, 0);
  delay(18);
  pinMode(dht, INPUT);

  for(i=0; i<MAX_TIMINGS;i++)
  {
     counter=0;

     while( digitalRead(dht) == laststate)
     {
       counter++;
       delayMicroseconds(1);
       if(counter ==255)break;
     }

     laststate=digitalRead(dht);
     if(counter==255)break;  
     if((i>=4)&&(i%2==0))
     {
       data[j/8]<<=1;
       if(counter > 16)data[j/8] |=1;
       j++;
     }
}
    
 if( (j>=40) && ( data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xff)) )
 {
   int h =(int)data[0];
   int c =(int)(data[2]&0x7f);
   if(data[2] & 0x80)c=-c;
   printf("humidity =%d ,  Temp=%d *C\n",h,c);
 }
 else printf("data not good,skip\n");
}

int main(void) {

	printf("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	if(wiringPiSetup() == -1)
	{
			  printf("wiringPiSetup() is failed :\n");
			  return 1;
	}
 
	while(1)
	{
		read_dht_data();
		delay(2000);
	}
	
	return EXIT_SUCCESS;
}
