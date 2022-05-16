#include "raspiPigpio.h"


void RaspiPigpio::initialise()
{
    if(gpioInitialise() < 0)
    {
        throw std::runtime_error("Pigpio gpioInitialise() failed.");
    }
}
