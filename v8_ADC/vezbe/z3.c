//Koristeći senzor osvetljaja na YL-40 modulu realizovati svetlosni detektor 
//sa rezolucijom tri nivoa (SLABO, DNEVNO, NOCNO) koje prikazivati na LED na DVK512.

#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <lcd.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define COLUMNS 16
#define LCD_RS 3
#define LCD_E 14
#define LCD_D4 4
#define LCD_D5 12
#define LCD_D6 13
#define LCD_D7 6

const char PCF8591 = 0x48; // adresa
int fd,adcVal,lcd;

int main()
{
	if (wiringPiSetup () == -1) exit (1);
	fd = wiringPiI2CSetup(PCF8591);
	if(lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4,LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0))
	{
		printf ("lcdInit nije uspeo! \n");
		return -1;
	}
	while (1)
	{
		lcdClear(lcd);
		// procitaj trimer pot sa AIN3 ulaza
		wiringPiI2CReadReg8(fd, PCF8591 + 0) ; // dummy
		adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 0) ;
		printf("Digitalna vrednost = %d \n ", adcVal);
		lcdPosition(lcd,0,0);
		if(adcVal >= 0 && adcVal < 86)
			lcdPrintf(lcd,"DNEVNO");
		if(adcVal > 85 && adcVal < 171)
                        lcdPrintf(lcd,"SLABO");
		if(adcVal > 170 && adcVal <= 255)
                        lcdPrintf(lcd,"NOCNO");
		delay(500);
	}
	return 0;
}

