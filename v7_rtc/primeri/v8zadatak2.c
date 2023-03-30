#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
//#include <stdlib.h>

#define changeHexToInt(hex) ((((hex)>>4) *10 ) + ((hex)%16) )
//adrese registara
#define SEK 0x02
#define MIN 0x03
#define SAT 0x04

const char PCF8563 = 0x51;
unsigned char WriteBuf[3];
unsigned char g8563_Store[3];
unsigned char init8563_Store[3]={0x00,0x59,0x08};

int fdes;

void P8563_settime()
{
	WriteBuf[0] = SEK;
	WriteBuf[1] = g8563_Store[0];
	//WriteBuf[0] = changeHexToInt(WriteBuf[0]);
	wiringPiI2CWriteReg8(fdes,WriteBuf[0],WriteBuf[1]);
	
	WriteBuf[0] = MIN;
        WriteBuf[1] = g8563_Store[1];
        //WriteBuf[0] = changeHexToInt(WriteBuf[0]);
        wiringPiI2CWriteReg8(fdes,WriteBuf[0],WriteBuf[1]);

	WriteBuf[0] = SAT;
        WriteBuf[1] = g8563_Store[2];
        //WriteBuf[0] = changeHexToInt(WriteBuf[0]);
        wiringPiI2CWriteReg8(fdes,WriteBuf[0],WriteBuf[1]);
}

void P8563_init()
{
	unsigned char i;
	
	for(i=0;i<3;i++)
		g8563_Store[i]=init8563_Store[i];
	P8563_settime();
	printf("Postavi početno tekuće vreme\n");
	//inicijalizacija RTC-a
	WriteBuf[0] = 0x0;
	WriteBuf[1] = 0x00; //normalni rezim rada
	//WriteBuf[0] = changeHexToInt(WriteBuf[0]);
	wiringPiI2CWriteReg8(fdes,WriteBuf[0],WriteBuf[1]);
}

void P8563_Readtime()
{
	//unsigned char time[7];
	//WriteBuf[0] = SEK;
	g8563_Store[0] = wiringPiI2CReadReg8(fdes,SEK);
	g8563_Store[1] = wiringPiI2CReadReg8(fdes,MIN);
	g8563_Store[2] = wiringPiI2CReadReg8(fdes,SAT);

	g8563_Store[0] = g8563_Store[0] & 0x7f;
	g8563_Store[1] = g8563_Store[1] & 0x7f;
	g8563_Store[2] = g8563_Store[2] & 0x3f;
	/*g8563_Store[0] = g8563_Store[0] & 0x7f;
	g8563_Store[1] = g8563_Store[1] & 0x7f;
	g8563_Store[2] = g8563_Store[2] & 0x3f;*/

	g8563_Store[0] = changeHexToInt(g8563_Store[0]);
	g8563_Store[1] = changeHexToInt(g8563_Store[1]);
	g8563_Store[2] = changeHexToInt(g8563_Store[2]);
}

int main(int argc, char **argv)
{
	wiringPiSetup();
		
	fdes = wiringPiI2CSetup(PCF8563);
	// adresa PCF8563 na I2C magistrali

	printf("start..........\n");
	P8563_init() ;
	while(1)
	{
		P8563_Readtime();
		printf("Sati:%d Minuti:%d Sekunde:%d\n",g8563_Store[2], g8563_Store[1],g8563_Store[0]);	
		delay(5000);
	}

	//bcm2835_i2c_end();
	//bcm2835_close();
	return 0;
}
