#include "mcp9808.h"


Mcp9808::Mcp9808() : PigpioI2c(0x18) // standard address for sensor when no address pins connected
{
    print("Temperature sensor found.", ROS_DEBUG);

    pushConfig_();
}


/**
 * @brief Read temperature from sensor and return it as a float value in degrees Celsius.
 * @return temperature in degrees Celsius.
 */
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


/**
 * @brief Print temperature to console in degrees Celsius.
 * @param decimalPlaces: How many decimal places are printed.
 */
void Mcp9808::printTemperature(const unsigned char decimalPlaces)
{
    float temperature = readTemperature();

    printf("Temperature : %.*f °C\n", decimalPlaces, temperature);
    fflush(stdout);
}


/**
 * @brief Print to the console the configuration register of the temperature sensor in binary (16bits)
 */
void Mcp9808::printConfig()
{
    unsigned int data;

    data = readWordData(configReg_);

    std::stringstream ss;
    ss << "Config recv : " << "0b" << std::bitset<16>{static_cast<unsigned>(data)};
    print(ss.str(), ROS_INFO);
}


/**
 * @brief Write the configuration register with the data saved in the private variable.
 */
void Mcp9808::pushConfig_()
{
    writeWordData(configReg_, configRegData_);
}
