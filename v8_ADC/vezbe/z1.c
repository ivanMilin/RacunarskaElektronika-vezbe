//Koristeći wiringPi biblioteku napraviti jednostavan voltmetar na LCD displeju koji meri napon u opsegu 0-3.3 V.

                                  //odabrao sam da citam trimer AIN3 ulaz
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
double analVr;

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
		wiringPiI2CReadReg8(fd, PCF8591 + 3) ; // dummy
		adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 3) ;
		printf("Digitalna vrednost = %d \n ", adcVal);
		analVr = (double)adcVal * 3.3/255;
		lcdPosition(lcd,0,0);
		lcdPrintf(lcd,"%.1f",analVr);
		delay(500);
	}
	return 0;
}

