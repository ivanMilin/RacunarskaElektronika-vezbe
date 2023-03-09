// treptanje led svakih 0.5 s

#include <bcm2835.h>

// LED je na DVK512 pločici na GPIO.28 (LED3)
// što je pin 20 na BCM-u

#define PIN 20

int main(int argc, char **argv)
{
     if (!bcm2835_init())
        return 1;
 
    // Setuj pin kao izlazni
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
 
    while (1)
    {
       // ukljuci
        bcm2835_gpio_write(PIN, HIGH);
        bcm2835_delay(500);

        // iskljuci
        bcm2835_gpio_write(PIN, LOW);
        bcm2835_delay(500);
    }
    
    bcm2835_close();
    return 0;
}

//gcc -o blink blink.c -l bcm2835
//./blink