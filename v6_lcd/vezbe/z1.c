#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <errno.h>
#include <wiringPi.h>
#include <lcd.h>

#define COLUMNS 16
#define LCD_RS 3
#define LCD_E 14
#define LCD_D4 4
#define LCD_D5 12
#define LCD_D6 13
#define LCD_D7 6


int fd = -1, ret;
char *tmp1, tmp2[10];
//char dev_name[] = "/sys/devices/w1_bus_master1/28-0000088b54dc/w1_slave";
char buffer[100];

long value, reminder;
int lcd;

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
	
	while(1)
	{
		if ((fd = fopen(dev_name, O_RDONLY)) < 0)
		{
			perror("Greska pri otvaranju!\n");
			exit(1);
		}
		ret = read(fd, buffer, sizeof(buffer));
		if (ret < 0)
		{
			perror("Greska pri citanju!\n");
			exit(1);			
		}
		
		tmp1 = strchr(buffer, 't');
		sscanf(tmp1, "t=%s", tmp2);
		value = atoi(tmp2);
		reminder = value%1000;
		value = value/1000;
		
		lcdPosition(lcd, 0, 0);
		lcdPrintf(lcd, "Temperatura je:");
		lcdPosition(lcd, 0, 1);
		lcdPrintf(lcd, "%d.%dC", value, reminder);
		delay(100);
	}
	
	close(fd);
	return 0;	
	
}
