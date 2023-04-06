#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <errno.h>
#include <wiringPi.h>
#include <lcd.h>

#include <wiringPiI2C.h>

#define COLUMNS 16
#define LCD_RS 3
#define LCD_E 14
#define LCD_D4 4
#define LCD_D5 12
#define LCD_D6 13
#define LCD_D7 6


const char PCF8591 = 0x48;
int fd, adcVal;
int lcd;
int procenat;

int main (int argc, char *argv[])
{
	if (wiringPiSetup() < 0){
		fprintf (stderr, "Greška pri inicijalizaciji:%s\n", strerror (errno)) ;
		return 1 ;
	}
	if (lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E, 
						LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0)){
		printf("lcdInit neuspesan!\n");
		return -1;	
	}
	
	fd = wiringPiI2CSetup(PCF8591);
	
	while(1)
	{
		wiringPiI2CReadReg8(fd, PCF8591 + 3) 
		adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 3) ;
		
		lcdPosition(lcd, 0, 0);
		lcdPrintf(lcd, "%d%", (adcVal/255)*100);
		
		lcdPosition(lcd, 0, 1);
		switch(adcVal){
			case 0 ... 85:
				lcdPrintf(lcd, "DNEVNO");
			case 86 ... 170:
				lcdPrintf(lcd, "SLABO");
			case 171 ... 255:
				lcdPrintf(lcd, "NOCNO");
			
		}
		delay(500);
	}
	
	close(fd);
	return 0;	
	
}
