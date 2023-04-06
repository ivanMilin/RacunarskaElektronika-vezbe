// Realizovati generator testerastog/trougaonog napona. 
// Ispravnost rada pokazati na osciloskopu

#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcd.h>
const char PCF8591 = 0x48; // adresa
int fd, adcVal;

int niz1 = 255;

int niz2 = 0;



int main()
{
	//int lcd_h;
	double vrednost_napona;
	
	if (wiringPiSetup () == -1) exit (1);
		fd = wiringPiI2CSetup(PCF8591);
	int smer = 1;
	int i = 0;
	int j = 50;
	while (1)
	{
		/*
		// procitaj trimer pot sa AIN3 ulaza
		wiringPiI2CReadReg8(fd, PCF8591 + 3) ; // dummy
		adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 3) ;
		printf("Pot ADC vrednost = %d \n", adcVal);
		*/
		if(smer)
		{
			// upisi tu vrednost u DAC reg, 0x04
		wiringPiI2CWriteReg8 (fd, PCF8591 + 4, niz1 - i) ;
	
		// procitaj DAC preko AIN2
		wiringPiI2CReadReg8(fd, PCF8591 + 15) ; // dummy
		adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 15);
		printf("DAC vrednost = %d \n\n" , niz1 - i);
		delay(500);
		i += 50;
		if(niz1 - i < 0)
			{
				i = 0;
				smer = 0;
			}
		}
		else
		{
		wiringPiI2CWriteReg8 (fd, PCF8591 + 4, niz2 + j) ;
	
		// procitaj DAC preko AIN2
		wiringPiI2CReadReg8(fd, PCF8591 + 15) ; // dummy
		adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 15);
		printf("DAC vrednost = %d \n\n" , niz2 + j);
		delay(500);
		j += 50;
		if(niz2 + j > 255)
			{
				j = 50;
				smer = 1;
			}
		}
		/*// upisi tu vrednost u DAC reg, 0x04
		wiringPiI2CWriteReg8 (fd, PCF8591 + 4, adcVal) ;
	
		// procitaj DAC preko AIN2
		wiringPiI2CReadReg8(fd, PCF8591 + 2) ; // dummy
		adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 2);
		printf("DAC vrednost = %d \n\n" , adcVal);
		delay(500);*/
	}
	
	return 0;
}
