#ifndef MCP9808_H
#define MCP9808_H

#include "pigpioI2c.h"


/**
 * @brief The Mcp9808 class creates a cpp interface for the temperature sensor mcp9808 for raspberry Pi.
 * @note The i2c interface must be enabled and configured on the raspberry pi.
 */
class Mcp9808 : public PigpioI2c
{
public:
    Mcp9808() : PigpioI2c(0x18) {}; // standard address for sensor when no address pins connected
    Mcp9808(unsigned char i2cAddr) : PigpioI2c(i2cAddr) {};
    Mcp9808(unsigned char i2cAddr, unsigned char i2cBus) : PigpioI2c(i2cAddr, i2cBus) {};
    void initialise();
    void initialise(bool initialiseRaspiPigpio);

private:
};

#endif // MCP9808_H
