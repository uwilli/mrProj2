#ifndef PCA9554B_H
#define PCA9554B_H

#include "pigpioI2c.h"

/**
 * @brief The Pca9554b class supports the ioExpander with functionality as is useful for the mrProj1 FHGR PCB
 */
class Pca9554b : public PigpioI2c
{
public:
    Pca9554b();
    void allOff();
    void setOutput(const unsigned char config);

    // Motor 4
    void m4Cw();
    void m4Ccw();
    void m4Off();

    // Leds
    void ledAll(const bool on);
    void ledFront(const bool on);
    void ledRear(const bool on);
    void ledSet(const unsigned char config);

    // Button
    bool readButton();

private:
    // Registers
    const char configReg_ = 0x03;
    const char inputReg_ = 0x00; // read only
    const char outputReg_ = 0x01; // if read, reflects what was written to register, not actual state of pin.

    // Config
    const unsigned char config_ = 0b10100011; // 1 = high impedance input, 0 = output
};

#endif // PCA9554B_H
