// NA DVK512 ploči se koristi KEY0 i LED3,
// a LED0 svetli dok taster nije pritisnut

#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

int main() {
	int i=0, taster_pritisnut=0;
	int r_value;

	if (wiringPiSetup() == -1)
		exit(1);

	pinMode(21, INPUT);
	pinMode(25, OUTPUT);

	digitalWrite(25, HIGH);

	if (softPwmCreate(28, 0, 100) != 0)
		exit (2);

	i = 0;
	taster_pritisnut = 0;

	while (1) {
		r_value = digitalRead(21); // procitaj KEY0
		digitalWrite(25, r_value);

		//cekamo na pritisak tastera

		if (!r_value && !taster_pritisnut) {
		
		taster_pritisnut = 1;
		
		i += 20;
		if (i > 100) 
			i = 0;

		printf("i = %d\n", i);
		fflush(stdout);

		softPwmWrite(28, i);
		}

	// cekamo da se taster otpusti
	if (r_value) taster_pritisnut = 0;
	}

return 0;
}