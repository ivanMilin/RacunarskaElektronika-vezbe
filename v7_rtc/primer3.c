#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <lcd.h>
#include <string.h>

#define changeHexToInt(hex) ((((hex)>>4) *10 ) + ((hex)%16) )
//adrese registara
#define SEK 0x02
#define MINUT 0x03
#define SAT 0x04
#define DAN 0x05
#define MES 0x07
#define GOD 0x08

#define COLUMNS 16
#define LCD_RS 3
#define LCD_E 14
#define LCD_D4 4
#define LCD_D5 12
#define LCD_D6 13
#define LCD_D7 6

unsigned char WriteBuf[2];
unsigned char ReadBuf;
unsigned char g8563_Store[6];
int lcd; // za LCD
							  //  sec,  min,  sat,  dan,  mes,  god
unsigned char init8563_Store[6]={0x00, 0x59, 0x08, 0x01, 0x04, 0x21};
 
void P8563_settime(int fd)
{
	wiringPiI2CWriteReg8(fd, SEK, g8563_Store[0]);
	wiringPiI2CWriteReg8(fd, MINUT, g8563_Store[1]);
	wiringPiI2CWriteReg8(fd, SAT, g8563_Store[2]);
	wiringPiI2CWriteReg8(fd, DAN, g8563_Store[3]);
	wiringPiI2CWriteReg8(fd, MES, g8563_Store[4]);
	wiringPiI2CWriteReg8(fd, GOD, g8563_Store[5]);
}

void P8563_init(int fd)
{
	unsigned char i;
	
	for(i = 0; i <= 5; i++)
		g8563_Store[i] = init8563_Store[i];

	P8563_settime(fd);
	printf("Postavi početno tekuće vreme i datum\n");

	//inicijalizacija RTC-a
	wiringPiI2CWriteReg8(fd, 0x00, 0cx0);
}

void P8563_Readtime(fd)
{
	unsigned char time[6];
	
	time[0] = wiringPiI2CReadReg8(fd, SEK);
	time[1] = wiringPiI2CReadReg8(fd, MINUT);
	time[2] = wiringPiI2CReadReg8(fd, SAT);
	time[3] = wiringPiI2CReadReg8(fd, DAN);
	time[4] = wiringPiI2CReadReg8(fd, MES);
	time[5] = wiringPiI2CReadReg8(fd, GOD);
	

	g8563_Store[0] = time[0] & 0x7f; // sekunde
	g8563_Store[1] = time[1] & 0x7f; // minuti
	g8563_Store[2] = time[2] & 0x3f; // sati
	g8563_Store[3] = time[3] & 0x3f; // dani
	g8563_Store[4] = time[4] & 0x1f; // meseci
	g8563_Store[5] = time[5]; // godine

	g8563_Store[0] = changeHexToInt(g8563_Store[0]);
	g8563_Store[1] = changeHexToInt(g8563_Store[1]);
	g8563_Store[2] = changeHexToInt(g8563_Store[2]);
	g8563_Store[3] = changeHexToInt(g8563_Store[3]);
	g8563_Store[4] = changeHexToInt(g8563_Store[4]);
	g8563_Store[5] = changeHexToInt(g8563_Store[5]);
}

void Dec2String(unsigned char num, char *str)
{
	if(num < 10)
	{
		str[0] = num + 48;
		str[1] = 0;
	}
	else
	{
		str[0] = num / 10 + 48;
		str[1] =  num % 10 + 48; 
		str[2] = 0;
	}
} 

int main(int argc, char **argv)
{
	int fd;
	
	if((wiringPiSetup() == -1))
		return 1;
	
	if(lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0))
	{
		printf ("lcdInit nije uspeo! \n");
		return -1 ;
	}
	
	fd = wiringPiI2CSetup(0x51);
	if(fd == -1)
	{
		printf("Greska pri radu sa I2C\n");
		return -1;
	}
	
	P8563_init(fd);

	while(1)
	{
		
		char *str1 = "Sati: ";
		char *str2 = " Minuti: ";
		char *str3 = " Sekunde: ";
		char nstr1[3], nstr2[3], nstr3[3];

		P8563_Readtime(fd);
		
		lcdPosition(lcd, 0, 0);
		Dec2String(g8563_Store[2], nstr1);
		Dec2String(g8563_Store[1], nstr2);
		Dec2String(g8563_Store[0], nstr3);
		strcat(str1, nstr1);
		strcat(str1, str2);
		strcat(str1, nstr2);
		strcat(str1, str3);
		strcat(str1, nstr3);
		lcdPuts(lcd, str1); // postavi vreme
		
		lcdPosition(lcd, 0, 1);
		Dec2String(g8563_Store[3], nstr1); // dani
		Dec2String(g8563_Store[4], nstr2); // meseci
		Dec2String(g8563_Store[5], nstr3); // godine
		strcat(nstr1, ":");
		strcat(nstr1, nstr2);
		strcat(nstr1, ":");
		strcat(nstr1, nstr3);
		lcdPuts(lcd, nstr1); // postavi datum
		
		
		// printf("Sati:%d Minuti:%d Sekunde:%d\n", g8563_Store[2], g8563_Store[1], g8563_Store[0]);
		// printf("%d:%d:%d\n", g8563_Store[3], g8563_Store[4], g8563_Store[5]);
		delay(2000);
	}

	return 0;
}
