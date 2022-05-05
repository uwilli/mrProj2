/**
* Simple implementation of an i2c scanner with pigpio.
*
* @author urban
*/

#include <stdio.h>
#include <signal.h>
#include "pigpio.h"

/*
// Defined directly in raspi when activating i2c
#define PIN_SDA 2
#define PIN_SCL 3
#define I2C_BUS 1
#define I2C_FREQ 400000
*/

int main()
{
	printf("\nHelloI2cScanner\n");
	if(gpioInitialise() < 0)
	{
	printf("Initialise failed\n");
		return -1;
	}
	
	int i2c_handle;
	for(int i=1; i<128; i++)
	{
		// changed to 7bit address inside of function!
		i2c_handle = i2cOpen(I2C_BUS, i, 0); // Last argument must always be zero, i2c flags not currently not defined.
		if(i2c_handle >= 0)
		{
			if(i2cWriteByte(i2c_handle, 0) >= 0)
			{
				printf("Found a device at address 0x%02X, assigned handle %i.\n", i, i2c_handle);
				i2cClose(i2c_handle);
			}
		}
	}
	
	return 0;
}