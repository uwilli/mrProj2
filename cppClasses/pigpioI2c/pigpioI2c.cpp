#include "pigpioI2c.h"


PigpioI2c::PigpioI2c(unsigned char i2cAddr)
{
    i2cAddr_ = i2cAddr;
}

PigpioI2c::PigpioI2c(unsigned char i2cAddr, unsigned char i2cBus)
{
    i2cAddr_ = i2cAddr;
    i2cBus_ = i2cBus;
}

PigpioI2c::~PigpioI2c()
{
    i2cClose(i2cHandle_);
}

void PigpioI2c::i2cScanner()
{
    i2cScanner(1); // standard i2c bus Raspi is 1
}

void PigpioI2c::i2cScanner(unsigned char i2cBus)
{
    RaspiPigpio bus;
    bus.initialise();

    int i2c_handle;
    for(int i=1; i<128; i++)
    {
        // changed to 7bit address inside of function!
        i2c_handle = i2cOpen(i2cBus, i, 0); // Last argument must always be zero, i2c flags not currently not defined.
        if(i2c_handle >= 0)
        {
            if(i2cWriteByte(i2c_handle, 0) >= 0)
            {
                printf("I2C device at address 0x%02X\n", i);
                i2cClose(i2c_handle);
            }
        }
    }
}

void PigpioI2c::initialise()
{
    char i2cHandle = -1;

    RaspiPigpio::initialise();

    i2cHandle = i2cOpen(i2cBus_, i2cAddr_, 0); // Last argument must always be zero, i2c flags not currently not defined in pigpio.
    if(i2cHandle < 0)
    {
        throw std::runtime_error("Failed to open i2c communication. (i2cOpen() pigpio)");
    }

    std::stringstream ssHex;
    ssHex << "0x" << std::hex << std::uppercase << static_cast<unsigned>(i2cAddr_); // otherwise unsigned char as ascii character
    i2cAddrHex_ = ssHex.str();

    if(i2cWriteByte(i2cHandle, 0) < 0)
    {
        i2cClose(i2cHandle);
        std::cout << "No device found at address : " << i2cAddrHex_ << std::endl;
    }
    else
    {
        i2cHandle_ = i2cHandle;
        std::cout << "Device is here and working." << std::endl;
    }
}

unsigned char PigpioI2c::getI2cBus()
{
    return i2cBus_;
}

unsigned char PigpioI2c::getI2cAddr()
{
    return i2cAddr_;
}




