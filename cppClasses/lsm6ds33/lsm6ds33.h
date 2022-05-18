#ifndef LSM6DS33_H
#define LSM6DS33_H

#include "pigpioI2c.h"

/**
 * @brief The Lsm6ds33 class creates a cpp interface for the gyroscope and magnetic sensor LSM6DS33 for raspberry Pi.
 * @note The i2c interface must be enabled and configured on the raspberry pi.
 */
class Lsm6ds33 : public PigpioI2c
{
public:
    Lsm6ds33() : PigpioI2c(0x6A) {}; //address for gyro and accelerometer
    void initialise();
    unsigned int setGyroMaxDPS(unsigned int gyroMaxDPS); // rounds them to nearest possible value and returns chosen one.

private:
    // Registers
    const char gyroSetupReg_ = 0x11;
    const char accSetupReg_ = 0x10;
    const char dataReg_ = 0x22; // gyro: 0x22-0x27, acc: 0x28-0x2D

    // Config
    unsigned int gyroMaxDPS_ = 500; // degrees per second
    unsigned int gyroFreqMode = 1; // 12.5Hz
    unsigned int accFreqMode = 1; // 12.5Hz
    unsigned int accMaxG = 4;

    // Functions
    void pushGyroMaxDPS();

};

#endif // LSM6DS33_H
