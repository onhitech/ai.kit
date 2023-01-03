/*
 ============================================================================
 Name        : i2c_fnd.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#define scan0 23
#define scan1 22
#define scan2 21
#define scan3 30

#define uint8_t unsigned char
#define uint16_t unsigned int

uint8_t FND[10];
int fd;

void BlinkFND(int* handle, uint16_t num)
{
int fd;
    /* 각 자리의 숫자 추출 */ 
	uint16_t n1 = (num % 10000) / 1000;
	uint16_t n2 = (num % 1000) / 100;
	uint16_t n3 = (num % 100) / 10;
	uint16_t n4 = (num % 10) / 1;

	fd= *handle;

	      wiringPiI2CWriteReg8(fd, 0x02, FND[n1]);
		  digitalWrite(scan0, LOW);
		  delay(1);
		  
		//wiringPiI2CWriteReg8(fd, 0x02, 0xff);
		  digitalWrite(scan0, HIGH);

		  wiringPiI2CWriteReg8(fd, 0x02,  FND[n2]);
		  digitalWrite(scan1, LOW);
		  delay(1);
		  digitalWrite(scan1, HIGH);

		  wiringPiI2CWriteReg8(fd, 0x02,  FND[n3]);
		  digitalWrite(scan2, LOW);
		  delay(1);
		  digitalWrite(scan2, HIGH);

		  wiringPiI2CWriteReg8(fd, 0x02, FND[n4]);
		  digitalWrite(scan3, LOW);
		  delay(1);
		  digitalWrite(scan3, HIGH);

}

int main(void)
{
	int fd;

	FND[0] = 0xC0;
	FND[1] = 0xF9;
	FND[2] = 0xA4;
	FND[3] = 0xB0;
	FND[4] = 0x99;
	FND[5] = 0x92;
	FND[6] = 0x83;
	FND[7] = 0xD8;
	FND[8] = 0x80;
	FND[9] = 0x90;
	
	puts("!!!Hello Smart!!!"); /* prints !!!Hello Smart!!! */

	if(wiringPiSetup() == -1)
	{
	  puts("wiringPiSetup() is failed :\n");
	  return 1;
	}

	 pinMode(scan0, 1);
	 pinMode(scan1, 1);
	 pinMode(scan2, 1);
	 pinMode(scan3, 1);
	 
	 pinMode(27, 1);

	 digitalWrite(scan0, HIGH);
	 digitalWrite(scan1, HIGH);
	 digitalWrite(scan2, HIGH);
	 digitalWrite(scan3, HIGH);

	 if((fd = wiringPiI2CSetup(0x21))<0) {
	  printf("wiringPiI2CSetup failed:\n");
	 }

	 if(wiringPiI2CWriteReg8(fd, 0x06, 0) == -1){
	  printf("write failed...\n");
	 }

	 if(wiringPiI2CWriteReg8(fd, 0x07, 0) == -1){
		  printf("write failed...\n");
	 }

	 while(1)
	 {
	  BlinkFND(&fd, 1234);
	 }
	return EXIT_SUCCESS;
}
