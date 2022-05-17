#include "mcp9808.h"


void Mcp9808::initialise()
{
    PigpioI2c::initialise();
    std::cout << "Temperature sensor found." << std::endl;

    pushConfig();
}

float Mcp9808::readTemperature()
{
    int data = 0;
    int tempVal = 0;
    float temperature = 3000;

    data = i2cReadWordData(i2cHandle_, tempReg_);

    tempVal = ((data << 8) | (data >> 8)) & 0x1FFF;
    if(tempVal > 4095)
    {
        tempVal -= 8192;
    }
    temperature = tempVal * 0.0625;

    return temperature;
}

void Mcp9808::printTemperature(unsigned char decimalPlaces)
{
    float temperature = readTemperature();
    std::stringstream ss;
    ss << std::fixed << std::setprecision(decimalPlaces) << temperature;

    std::cout << "Temperature : " << ss.str() << " °C" << std::endl;
}

void Mcp9808::printConfig()
{
    int data;

    data = i2cReadWordData(i2cHandle_, configReg_);

    std::cout << "Config recv : " << "0b" << std::bitset<16>{static_cast<unsigned>(data)} << std::endl;
}

void Mcp9808::pushConfig()
{
    if(i2cWriteWordData(i2cHandle_, configReg_, configRegData_) < 0)
    {
        throw std::runtime_error("Writing to config register of MCP9808 failed.");
    }
}
