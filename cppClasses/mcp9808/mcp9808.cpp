#include "mcp9808.h"


void Mcp9808::initialise()
{
    PigpioI2c::initialise();
    std::cout << "Temperature sensor found." << std::endl;

    pushConfig_();
}

float Mcp9808::readTemperature()
{
    unsigned int data = 0;
    int tempVal = 0;
    float temperature = 3000;

    data = readWordData(tempReg_);

    tempVal = ((data << 8) | (data >> 8)) & 0x1FFF;
    if(tempVal > 4095)
    {
        tempVal -= 8192;
    }
    temperature = tempVal * 0.0625;

    return temperature;
}

void Mcp9808::printTemperature(const unsigned char decimalPlaces)
{
    float temperature = readTemperature();

    printf("Temperature : %.*f °C\n", decimalPlaces, temperature);
    fflush(stdout);
}

void Mcp9808::printConfig()
{
    unsigned int data;

    data = readWordData(configReg_);

    std::cout << "Config recv : " << "0b" << std::bitset<16>{static_cast<unsigned>(data)} << std::endl;
}

void Mcp9808::pushConfig_()
{
    writeWordData(configReg_, configRegData_);
}
