#include <wiringPi.h>

// na DVK512 4 LED su povezane na GPIO.25-GPIO.28
// sto su pinovi 25,26,27,28 (wiringPi oznake)
// konkretne veze pinova uvek mozete
// dobiti pozivom: gpio readall

char LED[]={25,26,27,28};
char i;
int main(){

    wiringPiSetup();

    for(i=0;i<4;i++)
        pinMode (LED[i],OUTPUT);
    
    while(1)
    {
        for(i=0;i<4;i++) {
    
            digitalWrite (LED[i], 1);
            delay (200);
            digitalWrite (LED[i], 0);
            delay (200);
        }
    }
}

//gcc blink.c -o blink -lwiringPi -lwiringPiDev
//./blink