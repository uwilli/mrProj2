#ifndef MCP9808_H
#define MCP9808_H

#include "pigpioI2c.h"
#include <bitset>


/**
 * @brief The Mcp9808 class creates a cpp interface for the temperature sensor mcp9808 for raspberry Pi.
 * @note The i2c interface must be enabled and configured on the raspberry pi.
 */
class Mcp9808 : public PigpioI2c
{
public:
    Mcp9808() : PigpioI2c(0x18) {}; // standard address for sensor when no address pins connected
    Mcp9808(const unsigned char i2cAddr) : PigpioI2c(i2cAddr) {};
    Mcp9808(const unsigned char i2cAddr, const unsigned char i2cBus) : PigpioI2c(i2cAddr, i2cBus) {};
    void initialise(); // sets sensor to continuous temperature reading, no alerts.
    float readTemperature();
    void printTemperature(const unsigned char decimalPlaces);
    void printConfig();

private:
    // Registers
    const char configReg_ = 0x01; // Location config register
    const char tempReg_ = 0x05; // Location temperature register
    // Config
    wchar_t configRegData_ = 0x00; // Power-up default, alert disabled

    void pushConfig_();
};

#endif // MCP9808_H
