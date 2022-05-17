/**
* Demo program, minimal implementation of a servo with pigpio.
* Sweeping from MINPULSE to MAXPULSE
*
* @author urban
*/


#include <stdio.h>
#include <signal.h>
#include "pigpio.h"

// Hardware timed on BCM pins 0-31
// Full hardware BCM 12, 18 channel 0 / BCM 13,19 channel 1
#define PIN 25 // BCM pin
#define MINPULSE 1000
#define MAXPULSE 2000

int run = 1;

// catch ^C
void stop(int signum)
{
   run = 0;
}

int main(int argc, char *argv[])
{
	printf("\nHelloSweep\n");
	if(gpioInitialise() < 0)
	{
	printf("Initialise failed\n");
		return -1;
	}
	
	gpioSetSignalFunc(SIGINT, stop);
	
	int pulse = MINPULSE;
	int up = 1;
	
	while(run)
	{
		gpioServo(PIN, pulse);
		
		pulse += up * 5;
		if(pulse > MAXPULSE)
		{
			pulse = MAXPULSE;
			up = -1;
		}
		if(pulse < MINPULSE)
		{
			pulse = MINPULSE;
			up = 1;
		}
		
		time_sleep(0.01); // 50 Hz needed is made by gpioServo, not sleep
		//printf("%i", pulse);
	}
	
	gpioServo(PIN, 0);
	gpioTerminate();

	return 0;
}

