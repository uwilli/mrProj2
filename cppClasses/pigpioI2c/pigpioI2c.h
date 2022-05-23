#ifndef PIGPIOI2C_H
#define PIGPIOI2C_H

#include "raspiPigpio.h"

#include <iostream>

/**
 * @brief Implementing pigpio.h c-Library i2c functionality in a cpp class.
 * @note The i2c interface must be enabled and configured on the raspberry pi.
 */
class PigpioI2c : public RaspiPigpio
{
public:
    PigpioI2c(const unsigned char i2cAddr);
    PigpioI2c(const unsigned char i2cAddr, const unsigned char i2cBus);
    ~PigpioI2c();
    static void i2cScanner();
    static void i2cScanner(const unsigned char i2cBus);
    void initialise(); // already opens I2C communication
    unsigned char getI2cBus();
    unsigned char getI2cAddr();
    unsigned char readByteData(const unsigned char reg);
    unsigned int readWordData(const unsigned char reg);
    void readI2cBlockData(const unsigned char reg, char* buffer, const unsigned int bytes);
    void writeByteData(const unsigned char reg, const unsigned char byte);
    void writeWordData(const unsigned char reg, const unsigned int word);

protected:
    unsigned char i2cBus_ = 1;
    unsigned char i2cAddr_ = 0;
    unsigned char i2cHandle_ = 0;
};

#endif // PIGPIOI2C_H
