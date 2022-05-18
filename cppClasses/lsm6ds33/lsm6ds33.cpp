#include "lsm6ds33.h"


unsigned int Lsm6ds33::setGyroMaxDPS(unsigned int gyroMaxDPS)
{
    switch (gyroMaxDPS) { // implemented as switch, because vector etc would be overkill.
    case 0 ... 187:
        gyroMaxDPS_ = 125;
        break;
    case 188 ... 375:
        gyroMaxDPS_ = 250;
        break;
    case 376 ... 750:
        gyroMaxDPS_ = 500;
        break;
    case 751 ... 1500:
        gyroMaxDPS_ = 1000;
        break;
    default:
        gyroMaxDPS_ = 2000;
    }

    pushGyroMaxDPS();
    return gyroMaxDPS_;
}

void Lsm6ds33::pushGyroMaxDPS()
{
    unsigned char val = 0; // dps value we want to send
    char reg = 0; // data from and to register

    switch (gyroMaxDPS_) {
    case 125:
        val = 0x10;
        break;
    case 250:
        val = 0x00;
        break;
    case 500:
        val = 0x04;
        break;
    case 1000:
        val = 0x08;
        break;
    case 2000:
        val = 0x0C;
        break;
    default:
        throw std::invalid_argument("max degrees per second has an illegal value. Review setter Method guards.");
    }

    reg = i2cReadByteData(i2cHandle_, gyroSetupReg_); // Read register from sensor
    if(reg < 0)
    {
        throw std::runtime_error("Could not read gyroscope setup register.");
    }

    reg &= 0xF0; // set DPS bits to zero
    reg |= val;

    if(i2cWriteByteData(i2cHandle_, gyroSetupReg_, reg) < 0)
    {
        throw std::runtime_error("Could not write to gyroscope setup register.");
    }
}
