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

/**
 * @brief initialise pigpio library.
 */
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

/**
 * @brief Set mode of gpioPin.
 * @param bcmPin: Gpio concerned, BCM numbering!
 * @param mode: mode 0-7, use constants defined in library, PI_INPUT, PI_OUTPUT ...
 */
void RaspiPigpio::pinSetMode(unsigned char bcmPin, unsigned mode)
{
    checkBcmPinValid_(bcmPin);

    if(gpioSetMode(bcmPin, mode) < 0)
    {
        throw std::runtime_error("Could not set mode of gpio pin");
    }
}

/**
 * @brief Write low or High to pin set to Output mode.
 * @param bcmPin: Gpio concerned, BCM numbering!
 * @param level: 1 --> HIGH, 0 --> LOW
 */
void RaspiPigpio::pinWrite(const unsigned char bcmPin, const bool level)
{
    checkBcmPinValid_(bcmPin);

    if(gpioWrite(bcmPin, level) < 0)
    {
        throw std::runtime_error("Could not write level to gpio pin");
    }
}

/**
 * @brief Read level of pin set to input
 * @param bcmPin: Gpio concerned, BCM numbering!
 * @return level: 1 --> HIGH, 0 --> LOW
 */
bool RaspiPigpio::pinRead(const unsigned char bcmPin)
{
    int level = 0;

    checkBcmPinValid_(bcmPin);

    level = gpioRead(bcmPin);
    if(level < 0)
    {
        throw std::runtime_error("Could not read level of gpio pin");
    }

    return level;
}

void RaspiPigpio::checkBcmPinValid_(const unsigned char bcmPin)
{
    bool valid = true;

    if(bcmPin == 0)
    {
        valid = false;
    }
    if(bcmPin > 27)
    {
        valid = false;
    }

    if(!valid)
    {
        throw std::invalid_argument("BCM-pin does not exist. Must be between 1 and 27.");
    }
}
