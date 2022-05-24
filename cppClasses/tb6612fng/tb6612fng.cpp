#include "tb6612fng.h"

/**
 * @brief Initialise Motor driver. All motors are turned off.
 */
void Tb6612fng::initialise()
{
    PigpioPwm::initialise();

    pinSetMode(pinIn1M3_, PI_OUTPUT);
    pinSetMode(pinIn2M3_, PI_OUTPUT);

    allOff();
}

/**
 * @brief Turn all motors off.
 */
void Tb6612fng::allOff()
{
    motMode_(0, 0);
}

/**
 * @brief Handle motor number 3. (Start, stop, forward, backward)
 * @param percent: Percent of speed, from -100 (full backwards) to 0 (stop) to 100 (full forwards)
 */
void Tb6612fng::m3(const int percent)
{
    if(abs(percent) > 100)
    {
        throw std::invalid_argument("Maximum of 100 percent for motor speed.");
    }

    if(percent >= 0)
    {
        motMode_(3, 2);
        hardwarePwm(pinPwmM3_, freq_, percent*10000);
    }
    else
    {
        motMode_(3, 1);
        hardwarePwm(pinPwmM3_, freq_, -percent*10000);
    }
}

/**
 * @brief Set motor mode.
 * @param motorNumber: 1-4 individual motors, 0 all motors off. (no other modes than 0).
 * @param mode: 0 --> High Impedance Mode
 *              1 --> Clockwise
 *              2 --> Counter-clockwise
 */
void Tb6612fng::motMode_(const unsigned char motorNumber, const unsigned char mode)
{
    switch (motorNumber) {
    case 0:
        pinWrite(pinIn1M3_, 0);
        pinWrite(pinIn2M3_, 0);
        hardwarePwm(pinPwmM3_, freq_, 0);
        break;
    case 3:
        switch (mode) {
        case 0:
            pinWrite(pinIn1M3_, 0);
            pinWrite(pinIn2M3_, 0);
            hardwarePwm(pinPwmM3_, freq_, 0);
            break;
        case 1:
            pinWrite(pinIn1M3_, 1);
            pinWrite(pinIn2M3_, 0);
            break;
        case 2:
            pinWrite(pinIn1M3_, 0);
            pinWrite(pinIn2M3_, 1);
            break;
        default:
            throw std::invalid_argument("Motor mode higher than 2 does not exist.");
        }
        break;
    default:
        throw std::invalid_argument("Only motor 3 is currently implemented.");
    }
}


