			// TASTERI KEY2 I KEY3 NIKOM NE RADE PA SAM MODIFIKOVAO ZADATAK,PRITISKOM NA KEY0 POVECAVA 1 SEKUND A KEY1 POVECAVA 1 DAN
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <lcd.h>


#define changeHexToInt(hex) ((((hex)>>4) *10 ) + ((hex)%16) )


//adrese registara
#define SEK 0x02
#define MIN 0x03
#define SAT 0x04
#define DAY 0X05
#define MONTH 0X07
#define YEAR 0x08


#define COLUMNS 16
#define LCD_RS 3
#define LCD_E 14
#define LCD_D4 4
#define LCD_D5 12
#define LCD_D6 13
#define LCD_D7 6

const char PCF8563 = 0x51;
unsigned char WriteBuf[2];
unsigned char g8563_Store[6];
unsigned char init8563_Store[6]={0x00,0x59,0x08,0x27,0x05,0x20};

int fdes;
int lcd;
int n = 0x27;

void P8563_settime()
{
	WriteBuf[0] = SEK;
	WriteBuf[1] = g8563_Store[0];
	wiringPiI2CWriteReg8(fdes,WriteBuf[0],WriteBuf[1]);

	WriteBuf[0] = MIN;
        WriteBuf[1] = g8563_Store[1];
        wiringPiI2CWriteReg8(fdes,WriteBuf[0],WriteBuf[1]);

	WriteBuf[0] = SAT;
        WriteBuf[1] = g8563_Store[2];
        wiringPiI2CWriteReg8(fdes,WriteBuf[0],WriteBuf[1]);

        WriteBuf[0] = DAY;
        WriteBuf[1] = g8563_Store[3];
        wiringPiI2CWriteReg8(fdes,WriteBuf[0],WriteBuf[1]);

        WriteBuf[0] = MONTH;
        WriteBuf[1] = g8563_Store[4];
        wiringPiI2CWriteReg8(fdes,WriteBuf[0],WriteBuf[1]);

        WriteBuf[0] = YEAR;
        WriteBuf[1] = g8563_Store[5];
        wiringPiI2CWriteReg8(fdes,WriteBuf[0],WriteBuf[1]);
}

void P8563_init()
{
	unsigned char i;

	for(i=0;i<6;i++)
		g8563_Store[i]=init8563_Store[i];
	P8563_settime();
	printf("Postavi početno tekuće vreme\n");
	//inicijalizacija RTC-a
	WriteBuf[0] = 0x0;
	WriteBuf[1] = 0x00;
	wiringPiI2CWriteReg8(fdes,WriteBuf[0],WriteBuf[1]);
}

void P8563_Readtime()
{
	g8563_Store[0] = wiringPiI2CReadReg8(fdes,SEK);
	g8563_Store[1] = wiringPiI2CReadReg8(fdes,MIN);
	g8563_Store[2] = wiringPiI2CReadReg8(fdes,SAT);
	g8563_Store[3] = wiringPiI2CReadReg8(fdes,DAY);
	g8563_Store[4] = wiringPiI2CReadReg8(fdes,MONTH);
	g8563_Store[5] = wiringPiI2CReadReg8(fdes,YEAR);


	g8563_Store[0] = g8563_Store[0] & 0x7f;
	g8563_Store[1] = g8563_Store[1] & 0x7f;
	g8563_Store[2] = g8563_Store[2] & 0x3f;
	g8563_Store[3] = g8563_Store[3] & 0x3f;
	g8563_Store[4] = g8563_Store[4] & 0x1f;
	g8563_Store[5] = g8563_Store[5] & 0xff;

	g8563_Store[0] = changeHexToInt(g8563_Store[0]);
	g8563_Store[1] = changeHexToInt(g8563_Store[1]);
	g8563_Store[2] = changeHexToInt(g8563_Store[2]);
	g8563_Store[3] = changeHexToInt(g8563_Store[3]);
	g8563_Store[4] = changeHexToInt(g8563_Store[4]);
	g8563_Store[5] = changeHexToInt(g8563_Store[5]);
}

int main(int argc, char **argv)
{
	int taster_pritisnut=0;
	int taster_pritisnut1=0;

	int r_value = 0;;
	int r_value1 = 0;

	wiringPiSetup();

	pinMode(21,INPUT);
	pinMode(22,INPUT);

	if(lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4,LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0))
	{
		printf ("lcdInit nije uspeo! \n");
		return -1 ;
	}

	fdes = wiringPiI2CSetup(PCF8563);

	printf("start..........\n");

	P8563_init();

	while(1)
	{
		printf("Pritisni zeljeni taster ako zelis \n");

		//KEY0  - povecava 1 sekund
		r_value = digitalRead(21);
		if(!r_value && !taster_pritisnut)
		{
			printf("USAO SAM U KEY0 PETLJU \n");
			taster_pritisnut = 1;

			delay(1000);
			P8563_Readtime();
                	printf("Sati:%d Minuti:%d Sekunde:%d Datum: %d.%d.%d\n",g8563_Store[2], g8563_Store[1],g8563_Store[0],g8563_Store[3], g8563_Store[4], g8563_Store[5]);
                	lcdClear(lcd);
                	lcdPosition(lcd,0,0);
                	lcdPrintf(lcd,"%d.%d.%d",g8563_Store[3], g8563_Store[4], g8563_Store[5]);
                	lcdPosition(lcd,0,1);
                	lcdPrintf(lcd,"%d:%d:%d",g8563_Store[2], g8563_Store[1],g8563_Store[0]);
		}
		if(r_value) taster_pritisnut = 0;

		//KEY1  - povecava 1 dan
                r_value1 = digitalRead(22);
                if(!r_value1 && !taster_pritisnut1)
                {
			printf("USAO SAM U KEY1 PETLJU \n");
                        taster_pritisnut1 = 1;
			
			n = n + 1;
        		wiringPiI2CWriteReg8(fdes,DAY,n);
                        P8563_Readtime();
                        printf("Sati:%d Minuti:%d Sekunde:%d Datum: %d.%d.%d\n",g8563_Store[2], g8563_Store[1],g8563_Store[0],g8563_Store[3], g8563_Store[4], g8563_Store[5]);
                        lcdClear(lcd);
                        lcdPosition(lcd,0,0);
                        lcdPrintf(lcd,"%d.%d.%d",g8563_Store[3], g8563_Store[4], g8563_Store[5]);
                        lcdPosition(lcd,0,1);
                        lcdPrintf(lcd,"%d:%d:%d",g8563_Store[2], g8563_Store[1],g8563_Store[0]);
                }
                if(r_value1) taster_pritisnut1 = 0;


		P8563_Readtime();
		printf("Sati:%d Minuti:%d Sekunde:%d Datum: %d.%d.%d\n",g8563_Store[2], g8563_Store[1],g8563_Store[0],g8563_Store[3], g8563_Store[4], g8563_Store[5]);
                lcdClear(lcd);
		lcdPosition(lcd,0,0);
		lcdPrintf(lcd,"%d.%d.%d",g8563_Store[3], g8563_Store[4], g8563_Store[5]);
		lcdPosition(lcd,0,1);
		lcdPrintf(lcd,"%d:%d:%d",g8563_Store[2], g8563_Store[1],g8563_Store[0]);
		
		delay(5000);
	}
	return 0;
}
