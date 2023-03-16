#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
char LED[] = {25,26,27,28};
char u;

double temperatura(void) //očitavanje temperature
{
	FILE *ft;
	char tekst[100];

	ft=fopen("/sys/bus/w1/devices/28-00000cfbb0e4/w1_slave","r");
	if(ft==NULL) return 0;

	int i=0;
	for(i=0;i<22;i++) //samo temperatura
		fscanf(ft,"%s", tekst);
	fclose(ft);
	//obrisati „t=”

	for(i=0;i<10;i++) tekst[i]=tekst[i+2];

	int temp=atoi(tekst); //prebaci u double
	double tem=(double)temp/1000;
	
	return tem;
};

void zapis(double temp) //log metod
{
	FILE * log;
	log=fopen("log","a+"); //otvoriti datoteku

	if(log==NULL) return;
	fprintf(log, "\n%.3f", temp);
	fclose(log);
};

int main(void)
{
	FILE * log;
	int cz=0, j=0;
	struct timespec ts1, ts2; //merenje vremena
	long czas;
	log=fopen("log","w");

	if(log==NULL) return 0;
	fprintf(log, "\n\t\t***Temperatura***\n Izmerena temperatura = %.3f \xC2\xB0 C\t C\n", temperatura());
	fclose(log);
	printf("\n\nPočetna Temp = %.3f \xC2\xB0 C", temperatura());
	
	printf("Unesi vrednist za alarm: ");

	double tr;

	scanf("%lf",&tr);
	int i = 0;

	wiringPiSetup();
	
	while(1)
	{
		j++; //broj iteracija
		clock_gettime(CLOCK_REALTIME, &ts1);
	double tem = temperatura();
	
	
	digitalWrite(LED[0], i);
	if(tem > tr)
	{
		if(i)
			i = 0;
		else
			i = 1;				
	}
	else i = 0;
	

	//printf("\n\nPočetna Temp = %.3f \xC2\xB0 C", temperatura());
	
	czas = (ts2.tv_nsec - ts1.tv_nsec)/1000000;
	if(czas <= 0) czas = czas + 999;
	
	//printf("\tTrajanje merenja %ld ms",czas);
		
	
	zapis(temperatura()); //upis u datoteku
	}
	return 0;
}