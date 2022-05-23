#include "pca9554b.h"

/**
 * @brief Initialises ioExpander and parent class.
 */
void Pca9554b::initialise()
{
    PigpioI2c::initialise();
    std::cout << "IO-Expander found." << std::endl;

    pushConfig_();
}

void Pca9554b::allOff()
{
    pushOutput_(0x00);
}

void Pca9554b::pushConfig_()
{
    writeByteData(configReg_, config_);
}

void Pca9554b::pushOutput_(const unsigned char byte)
{
    writeByteData(outputReg_, byte);
}
