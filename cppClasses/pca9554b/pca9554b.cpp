#include "pca9554b.h"

/**
 * @brief Initialises ioExpander and parent class.
 */
void Pca9554b::initialise()
{
    PigpioI2c::initialise();
    std::cout << "IO-Expander found." << std::endl;

    writeByteData(configReg_, config_);
}

/**
 * @brief Turn all outputs off. Has no effect on inputs.
 */
void Pca9554b::allOff()
{
    writeByteData(outputReg_, 0x00);
}

/**
 * @brief Set output register individually defining all eight values.
 * @param config: Output register to be set to these values. 0 --> P0, 7 --> P7
 */
void Pca9554b::setOutput(const unsigned char config)
{
    writeByteData(outputReg_, config);
}

/**
 * @brief Configure motor 4 to turn clockwise. PWM pulse must be set seperately.
 */
void Pca9554b::m4Cw()
{
    unsigned char output = 0;

    output = readByteData(outputReg_);

    output &= 0xFC; // Clear In1, In2
    output |= 0x01; // In1 = HIGH, In2 = LOW

    writeByteData(outputReg_, output);
}

/**
 * @brief Configure motor 4 to turn counter-clockwise. PWM pulse must be set seperately.
 */
void Pca9554b::m4Ccw()
{
    unsigned char output = 0;

    output = readByteData(outputReg_);

    output &= 0xFC; // Clear In1, In2
    output |= 0x02; // In1 = LOW, In2 = HIGH

    writeByteData(outputReg_, output);
}

/**
 * @brief Put motor 4 in high-impedance mode (off).
 */
void Pca9554b::m4Off()
{
    unsigned char output = 0;

    output = readByteData(outputReg_);

    output &= 0xFC; // Clear In1, In2

    writeByteData(outputReg_, output);
}

/**
 * @brief Turn all 4 leds off or on.
 * @param on: true --> on, false --> off
 */
void Pca9554b::ledAll(const bool on)
{
    unsigned char output = 0;
    unsigned char val = 0x00;

    if(on)
    {
        val = 0x5C;
    }

    output = readByteData(outputReg_);

    output &= 0xA3;
    output |= val;

    writeByteData(outputReg_, output);
}

/**
 * @brief Turn front Leds on or off.
 * @param on: true --> on, false --> off
 */
void Pca9554b::ledFront(const bool on)
{
    unsigned char output = 0;
    unsigned char val = 0x00;

    if(on)
    {
        val = 0x50;
    }

    output = readByteData(outputReg_);

    output &= 0xAF;
    output |= val;

    writeByteData(outputReg_, output);
}

/**
 * @brief Turn rear Leds on or off.
 * @param on: true --> on, false --> off
 */
void Pca9554b::ledRear(const bool on)
{
    unsigned char output = 0;
    unsigned char val = 0x00;

    if(on)
    {
        val = 0x0C;
    }

    output = readByteData(outputReg_);

    output &= 0xF3;
    output |= val;

    writeByteData(outputReg_, output);
}

/**
 * @brief Set configuration individually for all 4 leds.
 * @param config: Bits 0-3 indicate each led, 1 is on, 0 is off. Higher bits are discarded.
 *                Bit   0 --> Front Left
 *                      1 --> Front Right
 *                      2 --> Rear Left
 *                      3 --> Rear Right
 */
void Pca9554b::ledSet(const unsigned char config)
{
    unsigned char output = 0;
    unsigned char val = 0;
    unsigned char bit = 0;
    unsigned char map = 0x40;

    for(int i=0; i<3; i++)
    {
        bit = (config >> i) & 0x01; // = 1 if bit i is set to 1
        if(bit)
        {
            val |= map >> (i*2); // Bit that needs to be seed for corresponding Pin.
        }
    }
    if((config >> 3) & 0x01) // = Rear right Led pin does not follow logic above.
    {
        val |= 0x08;
    }

    output = readByteData(outputReg_);

    output &= 0xA3;
    output |= val;

    writeByteData(outputReg_, output);
}

/**
 * @brief Read logic level of button.
 * @return 1 if pressed, 0 if not pressed.
 */
bool Pca9554b::readButton()
{
    unsigned char level = 0;

    level = readByteData(inputReg_);
    level = level >> 7; // Only button is on eighth pin
    level = !level; // 0 if not pressed

    return level;
}
