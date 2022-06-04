#include "tb6612fng.h"


/**
 * @brief Create object for 1 motor. At the moment, only motor 3 implemented.
 */
Tb6612fng::Tb6612fng(const unsigned char motorNumber)
{
    switch (motorNumber)
    {
    case 1:
        pinIn1_ = 17;
        pinIn2_ = 27;
        pinPwm_ = 23; // no Hardware-PWM
    case 2:
        pinIn1_ = 18;
        pinIn2_ = 22;
        pinPwm_ = 24; // no Hardware-PWM
    case 3:
        pinIn1_ = 16;
        pinIn2_ = 25;
        pinPwm_ = 12;
        break;
    case 4:
        /* on io-Expander
        pinIn1_
        pinIn2_
        */
        pinPwm_ = 6; // no Hardware-PWM
    default:
        throw std::invalid_argument("Invalid motor number or motor not implemented (currently only motor 3 implemented)");
    }

    pinSetMode(pinIn1_, PI_OUTPUT);
    pinSetMode(pinIn2_, PI_OUTPUT);

    pinWrite(pinIn1_, 0);
    pinWrite(pinIn2_, 0); // High impedance mode
    hardwarePwm(pinPwm_, freq_, 0);
}

Tb6612fng::~Tb6612fng()
{
    pinWrite(pinIn1_, 0);
    pinWrite(pinIn2_, 0); // High impedance mode
    hardwarePwm(pinPwm_, freq_, 0);
}


/**
 * @brief Turn all the motors off. Only motor 3 implemented at the moment.
 */
void Tb6612fng::allOff()
{
    PigpioPwm manip;

    // motor 3
    manip.pinWrite(16, 0);
    manip.pinWrite(25, 0);
    manip.hardwarePwm(12, 0, 0);
}


/**
 * @brief Set a speed for the motor.
 * @param percent: 0 for high impedance mode, -100 to 100. Positive is counter-clockwise.
 */
void Tb6612fng::speed(const int percent)
{
    unsigned int speedMultiplier = abs(percent);

    if(percent == 0)
    {
        pinWrite(pinIn1_, 0);
        pinWrite(pinIn2_, 0); // High impedance mode
    }
    else if(percent > 0)
    {
        pinWrite(pinIn1_, 0);
        pinWrite(pinIn2_, 1); // CCW
    }
    else
    {
        pinWrite(pinIn1_, 1);
        pinWrite(pinIn2_, 0); // CW
    }

    if(speedMultiplier > 100)
    {
        speedMultiplier = 100;
    }

    hardwarePwm(pinPwm_, freq_, speedMultiplier*10000); // hardware Pwm function [0, 1M]
}


/**
 * @brief Put motor in high impedance mode.
 */
void Tb6612fng::off()
{
    pinWrite(pinIn1_, 0);
    pinWrite(pinIn2_, 0); // High impedance mode
    hardwarePwm(pinPwm_, freq_, 0);
}
