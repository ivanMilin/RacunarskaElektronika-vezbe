#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>

#define changeHexToInt(hex) ((((hex)>>4) *10 ) + ((hex)%16) )
//adrese registara
#define SEK 0x02
#define MIN 0x03
#define SAT 0x04
#define DAN 0x05
#define MES 0x07
#define GOD 0x08

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <lcd.h>
#include <string.h>

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
 
void P8563_settime()
{
	// sekundi
	WriteBuf[0] = SEK;
	WriteBuf[1] = g8563_Store[0];
	bcm2835_i2c_write(WriteBuf,2);
	
	// minuti
	WriteBuf[0] = MIN;
	WriteBuf[1] = g8563_Store[1];
	bcm2835_i2c_write(WriteBuf, 2);
	
	// sati
	WriteBuf[0] = SAT;
	WriteBuf[1] = g8563_Store[2];
	bcm2835_i2c_write(WriteBuf, 2);
	
	// dani
	WriteBuf[0] = DAN;
	WriteBuf[1] = g8563_Store[3];
	bcm2835_i2c_write(WriteBuf, 2);
	
	// meseci
	WriteBuf[0] = MES;
	WriteBuf[1] = g8563_Store[4];
	bcm2835_i2c_write(WriteBuf, 2);
	
	// godine
	WriteBuf[0] = GOD;
	WriteBuf[1] = g8563_Store[5];
	bcm2835_i2c_write(WriteBuf, 2);
}

void P8563_init()
{
	unsigned char i;
	
	for(i = 0; i <= 5; i++)
		g8563_Store[i] = init8563_Store[i];

	P8563_settime();
	printf("Postavi početno tekuće vreme i datum\n");

	//inicijalizacija RTC-a
	WriteBuf[0] = 0x0;
	WriteBuf[1] = 0x00; //normalni rezim rada
	bcm2835_i2c_write(WriteBuf, 2);
}

void P8563_Readtime()
{
	unsigned char time[7];
	
	WriteBuf[0] = SEK;
	bcm2835_i2c_write_read_rs(WriteBuf, 1, time, 7);

	g8563_Store[0] = time[0] & 0x7f; // sekunde
	g8563_Store[1] = time[1] & 0x7f; // minuti
	g8563_Store[2] = time[2] & 0x3f; // sati
	g8563_Store[3] = time[3] & 0x3f; // dani
	g8563_Store[4] = time[5] & 0x1f; // meseci
	g8563_Store[5] = time[6]; // godine

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
	
	if(!bcm2835_init() || (wiringPiSetup() == -1))
		return 1;
	
	if(lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0))
	{
		printf ("lcdInit nije uspeo! \n");
		return -1 ;
	}
	
	bcm2835_i2c_begin();
	// adresa PCF8563 na I2C magistrali
	bcm2835_i2c_setSlaveAddress(0x51);
	bcm2835_i2c_set_baudrate(10000);
	printf("start..........\n");
	P8563_init() ;

	while(1)
	{
		
		char *str1 = "Sati: ";
		char *str2 = " Minuti: ";
		char *str3 = " Sekunde: ";
		char nstr1[3], nstr2[3], nstr3[3];

		P8563_Readtime();
		
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
		
		bcm2835_delay(2000);
	}

	bcm2835_i2c_end();
	bcm2835_close();

	return 0;
}
