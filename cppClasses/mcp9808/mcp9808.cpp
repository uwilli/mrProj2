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
    float temperature = 3000;
    unsigned char upperByte;
    unsigned char lowerByte;

    data = i2cReadWordData(i2cHandle_, tempReg_);

    //std::cout << "0b" << std::bitset<16>{static_cast<unsigned>(data)} << "       ";

    upperByte = data >> 8;
    lowerByte = data & 0xFF;

    std::cout << "u: " << static_cast<unsigned>(upperByte) << "    l: " << static_cast<unsigned>(lowerByte) << "      ";

    // Temperature conversion as described in datasheet
    upperByte &= 0x1F; // delete upper 3 bits (alert bits)

    if((upperByte & 0x10) == 0x10) { // temp < 0
        upperByte &= 0x0F; // clear sign
        temperature = 256 - (upperByte*16 + lowerByte/16);
    }
    else
    {
        temperature = upperByte*16 + lowerByte/16;
    }


    std::cout << temperature << " deg C" << std::endl;

    return temperature;
}

void Mcp9808::printConfig()
{
    int data;

    data = i2cReadWordData(i2cHandle_, configReg_);

    std::cout << "Config recv : " << "0b" << std::bitset<16>{static_cast<unsigned>(data)} << std::endl;
}

void Mcp9808::pushConfig()
{
    std::cout << "Config sent : " << std::bitset<16>{static_cast<unsigned>(configRegData_)} << std::endl;
    if(i2cWriteWordData(i2cHandle_, configReg_, configRegData_) < 0)
    {
        throw std::runtime_error("Writing to config register of MCP9808 failed.");
    }
}
