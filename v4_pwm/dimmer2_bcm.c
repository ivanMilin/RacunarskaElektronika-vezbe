// PWM kontrola GPIO pinova upotrebom BCM2835 biblioteke
// i hardverskog PWM-a za dimovani blink LED
// gcc -o pwm4 pwm4.c -l bcm2835
// sudo ./pwm4

#include <bcm2835.h>
#include <stdio.h>

// PWM izlaz je na pin 12 na RPi2 GPIO prikljucku
// sto je BCM pin 18 u ALT fun broj 5
// ovo je jedini PWM pin slobodan na RPi GPIO
#define PIN 18

// koristi PWM kanal 0
#define PWM_CHANNEL 0

// max range PWM signala
#define RANGE 1024

int main(int argc, char **argv)
{
    if (!bcm2835_init())
    return 1;
 
    // Setuj izlazni pin u Alt Fun 5,
    // da bi PWM kanal 0 bio izlaz
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_ALT5);

    // Clock divider = 2048
    // Sa divider = 2048 i RANGE = 1024,
    // u MARKSPACE modu,
    // frekvencija ponavljanja impulsa
    // ce biti 19.2MHz/2048/1024= oko 18Hz

    bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_2048);
    bcm2835_pwm_set_mode(PWM_CHANNEL, 1, 1);
    bcm2835_pwm_set_range(PWM_CHANNEL, RANGE);

    // realizacija dimera promenom PWM odnosa u
    // opsegu 1/RANGE i (RANGE-1)/RANGE
    int direction = 1;
    int data = 1;
 
    while (1)
    {
        if (data == 1)
        direction = 1;
        else if (data == RANGE-1)
        direction = -1;
        data += direction;
        bcm2835_pwm_set_data(PWM_CHANNEL, data);
        bcm2835_delay(10);
    }
    
    bcm2835_close();
    return 0;
}