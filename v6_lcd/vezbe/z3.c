/*Napisati odgovarajući program u C-u za RPi koji omogućava ispis nekih ćiriličnih
karaktera koristeći CGRAM memoriju LCD-a na bazi Primera 2.*/

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
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

// č
char data0[8] = {0b01010, 0b00100, 0b00000, 
			     0b01110, 0b10000, 0b10000,
				 0b10000, 0b01110};
// ć				 
char data1[8] = {0b00010, 0b00100, 0b00000, 
			     0b01110, 0b10000, 0b10000,
				 0b10000, 0b01110;				
int lcd;

int main()
{
	if(lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0))
	{
		printf ("lcdInit nije uspeo! \n");
		return -1 ;
	}
	
	lcdCharDef(lcd, 0, data0);
	lcdCharDef(lcd, 1, data1);
	
	while(1)
	{
		lcdPosition(lcd, 0,0);
		lcdPutchar(lcd, 0);
		lcdPosition(lcd, 0,1);
		lcdPutchar(lcd, 1);
	}
	
	return 0;
}