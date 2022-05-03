/**
* Demo program, sweeping steering servo and running motor from full throttle backwards
* to full stop to full throttle forwards.
* Using Hardware PWM for motor and pigpio implementation for servo.
* (both hardware PWM did not work well, maybe because freq are so far apart? clock settings)
*
* @author urban
*/


#include <stdio.h>
#include <signal.h>
#include "pigpio.h"

// Hardware timed on BCM pins 0-31
#define PIN_PWM_MOTOR 12 // BCM pin
#define PIN_A_MOTOR 7 // forwards : A=0, B=1
#define PIN_B_MOTOR 8 
#define PWMFREQ_MOTOR 95000
#define MINPULSE_MOTOR 0
#define MAXPULSE_MOTOR 1000000 // 1 million

#define PIN_SERVO 13 // BCM pin
#define MINPULSE_SERVO 1300
#define MAXPULSE_SERVO 1700 // 1 million

int run = 1;

// catch ^C
void stop(int signum)
{
   run = 0;
}

int main(int argc, char *argv[])
{
	printf("\nHelloCarDemo\n");
	if(gpioInitialise() < 0)
	{
	printf("Initialise failed\n");
		return -1;
	}
	
	gpioSetSignalFunc(SIGINT, stop);
	
	
	int pulse_s = MINPULSE_SERVO;
	int up_s = 1;
	
	int pulse_m = MINPULSE_MOTOR;
	int up_m = 1;
	int state_m = -1;
	
	gpioSetMode(PIN_A_MOTOR, PI_OUTPUT);
	gpioSetMode(PIN_B_MOTOR, PI_OUTPUT);
	
	gpioWrite(PIN_A_MOTOR, 1);
	gpioWrite(PIN_B_MOTOR, 0); // A=1, B=0 is backwards
	
	int ret = 0; // return value gpio PWM functions
	
	while(run)
	{
	// Servo
		ret = gpioServo(PIN_SERVO, pulse_s);
		if( ret != 0)
		{
			printf("Servo-PWM failed, error code : %i", ret);
			run = 0;
		}
		
		pulse_s += up_s * 5;
		if(pulse_s >= MAXPULSE_SERVO)
		{
			pulse_s = MAXPULSE_SERVO;
			up_s = -1;
		}
		if(pulse_s <= MINPULSE_SERVO)
		{
			pulse_s = MINPULSE_SERVO;
			up_s = 1;
		}
		
	// Motor
		ret = gpioHardwarePWM(PIN_PWM_MOTOR, PWMFREQ_MOTOR, pulse_m);
		if( ret != 0)
		{
			printf("Hardware-PWM failed, error code : %i", ret);
			run = 0;
		}
		
		pulse_m += up_m * 5000;
		if(pulse_m >= MAXPULSE_MOTOR)
		{
			pulse_m = MAXPULSE_MOTOR;
			up_m = -1;
		}
		if(pulse_m <= MINPULSE_MOTOR)
		{
			pulse_m = MINPULSE_MOTOR;
			up_m = 1;
			
			if(state_m == -1)
			{
			gpioWrite(PIN_A_MOTOR, 0);
			gpioWrite(PIN_B_MOTOR, 0);
			state_m = 0;
			printf("Changed to state 0\n");
			continue;
			}
			if(state_m == 0)
			{
			gpioWrite(PIN_A_MOTOR, 0);
			gpioWrite(PIN_B_MOTOR, 1);
			state_m = 1;
			printf("Changed to state 1\n");
			continue;
			}
			if(state_m == 1)
			{
			gpioWrite(PIN_A_MOTOR, 1);
			gpioWrite(PIN_B_MOTOR, 0);
			state_m = -1;
			printf("Changed to state -1\n");
			continue;
			}
		}
		
		time_sleep(0.01); // 50 Hz needed is made by gpioServo, not sleep
		//printf("%i", pulse);
	}
	
	gpioServo(PIN_SERVO, 0);
	gpioHardwarePWM(PIN_PWM_MOTOR, 0, 0);
	gpioWrite(PIN_A_MOTOR, 0);
	gpioWrite(PIN_B_MOTOR, 0);
			
	gpioTerminate();

	return 0;
}