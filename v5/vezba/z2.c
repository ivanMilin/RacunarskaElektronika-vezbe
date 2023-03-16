#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wiringPi.h>
#include <sys/fcntl.h>
#define MAX 500
#define LED 25

int main()
{
	char path[] = "/sys/bus/w1/devices/28-0000088b54dc/w1_slave";
	float prag, temp;
	int c;
	FILE *fp;
	char* str;
	char* ch;
	pinMode(LED, OUTPUT);
	
	// ukljucivanje wiringPi biblioteke
	if(wiringPiSetup() == -1)
		exit(1);
	
	// Biranje praga
	printf("Odredite prag:\n");
	scanf("%f", &prag);
	
	while(1)
	{
		
		// Otvaranje fajla za citanje temperature
		fp = fopen(path, "r");
		if(fp == NULL)
		{
			printf("Greska prilikom otvaranja %s\n", sw_path);
			return -1;
		}
		
		for(c = 0; i < 22 ; i++) //samo temperatura
			fscanf(fp,"%s", str);
		ch = strchr(str, "t");
		ch += 2;
		
		if(fclose(fp))
		{
			printf("Greska prilikom zatvranja %s\n", sw_path);
			return -1;
		}
		
		c = atoi(ch);
		temp = (float)(c) / 1000.0;
		printf("Temperatura je: %.3f\n", temp);
		
		if(temp > prag)
		{
			digitalWrite(LED, 1);
			delay(500);
			digitalWrite (LED, 0);
			delay(500);
		}
	}
	
	return 0;
}