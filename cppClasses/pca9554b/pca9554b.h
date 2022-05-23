#ifndef PCA9554B_H
#define PCA9554B_H

#include "pigpioI2c.h"

/**
 * @brief The Pca9554b class supports the ioExpander with functionality as is useful for the mrProj1 FHGR PCB
 */
class Pca9554b : public PigpioI2c
{
public:
    Pca9554b() : PigpioI2c(0x20) {}; // address of io-Expander on mrProj1 PCB.
    void initialise();
    void allOff();

private:
    // Registers
    const char configReg_ = 0x03;
    const char inputReg_ = 0x00; // read only
    const char outputReg_ = 0x01; // if read, reflects what was written to register, not actual state of pin.

    // Config
    unsigned char config_ = 0b10100011; // 1 = high impedance input, 0 = output

    // Functions
    void pushConfig_();
    void pushOutput_(const unsigned char byte);
};

#endif // PCA9554B_H
