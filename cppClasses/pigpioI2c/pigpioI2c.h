#ifndef PIGPIOI2C_H
#define PIGPIOI2C_H

#include "raspiPigpio.h"

#include <iostream>
#include <sstream>

/**
 * @brief Implementing pigpio.h c-Library i2c functionality in a cpp class.
 * @note The i2c interface must be enabled and configured on the raspberry pi.
 */
class PigpioI2c : public RaspiPigpio
{
public:
    PigpioI2c(unsigned char i2cAddr);
    PigpioI2c(unsigned char i2cAddr, unsigned char i2cBus);
    void initialise();
    void initialise(bool initialiseRaspiPigpio);
    unsigned char getI2cBus();
    unsigned char getI2cAddr();

protected:
    bool initialiseRaspiPigpio_ = true;
    unsigned char i2cBus_ = 1;
    unsigned char i2cAddr_ = 0;
    unsigned char i2cHandle_ = 0;
};

#endif // PIGPIOI2C_H
