#include "raspiPigpio.h"



int RaspiPigpio::initialised_ = 0;


RaspiPigpio::~RaspiPigpio()
{
    initialised_ --;

    if(initialised_ < 1)
    {
        gpioTerminate();
        initialised_ = 0;
    }
}

void RaspiPigpio::initialise()
{
    if(initialised_ < 1)
    {
        if(gpioInitialise() < 0)
        {
            throw std::runtime_error("Pigpio gpioInitialise() failed.");
        }
    }
    initialised_ ++;
}
