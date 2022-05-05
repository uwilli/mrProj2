/**
* Demo program, minimal implementation of pwm for motor, <100kHz.
* Using Hardware PWM
* Sweeping from 0 to 100%
*
* @author urban
*/


#include <stdio.h>
#include <signal.h>
#include <pigpio.h>

// Hardware timed on BCM pins 0-31
#define PIN 12 // BCM pin
#define PWMFREQ 95000
#define MINPULSE 0
#define MAXPULSE 1000000 // 1 million

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
	int ret = 0;
	
	while(run)
	{
		ret = gpioHardwarePWM(PIN, PWMFREQ, pulse);
		if( ret != 0)
		{
			printf("Hardware-PWM failed, error code : %i", ret);
			run = 0;
		}
		
		pulse += up * 5000;
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
	
	gpioHardwarePWM(PIN, PWMFREQ, 0);
	gpioTerminate();

	return 0;
}