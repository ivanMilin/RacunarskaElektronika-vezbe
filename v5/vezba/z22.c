#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcnt1.h>
#include <wiringPi.h>

char LED[] = {25, 26, 27, 28};
char dev_name[] = "/sys/devices/w1_bus_master1/28-0000088b54dc/w1_slave";
int fd = -1, ret;
char buffer[100];
char *tmp1, tmp2[10];
long value;
float prag, temp;

int main (int argc, char *argv[])
{	

	if(wiringPiSetup() == -1)
		exit(1);
	
	for(i = 0; i < 4; i++){
		pinMode(LED[i], OUTPUT);
		digitalWrite(LED[i], 0);		
	}
	
	printf("Unesite zeljeni temperaturni prag: ");
	scanf("%f", &prag);
	
	while(1)
	{
		if((fd = open(dev_name, O_RDONLY)) < 0)
		{
			perror("Greska pri otvaranju !\n");
			exit(1);			
		}
		ret = read(fd, buffer, sizeof(buffer));
		if(ret < 0)
		{
			perror("Greska pri citanju!\n");
			exit(1);
		}
		
		tmp1 = strchr(buffer, 't');
		sscanf(tmp1, "t=%s", tmp2);
		value = atoi(tmp2);
		temp = (float)(value) / 1000.0;
		
		printf("Temperatura je: %.3f\n", temp);
		
		if(temp > prag)
		{
			digitalWrite(LED[0], 1);
			delay(500);
			digitalWrite(LED[0], 0);
			delay(500);
		}
		
	}
	return 0;
}