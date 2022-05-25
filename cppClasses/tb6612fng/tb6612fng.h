#ifndef TB6612FNG_H
#define TB6612FNG_H

#include "pigpioPwm.h"

/* TODO : move initialise to constructor, refactor code so that object refers to 1 motor.
 *
 *
 *
 */






/**
 * @brief Motor driver for TB6612FNG installed on mrProj1 FHGR PCB.
 * @note Only motor 3 implemented.
 */
class Tb6612fng : public PigpioPwm
{
public:
    void initialise();
    void allOff();
    void m3(const int percent);

private:
    // Adresses -- as reference. Only motor 3 implemented.
    /*
    const unsigned char pinPwmM1_ = 23; // no Hardware-PWM
    const unsigned char pinPwmM2_ = 24; // no Hardware-PWM
    */
    const unsigned char pinPwmM3_ = 12;
    /*
    const unsigned char pinPwmM4_ = 6; // no Hardware-PWM

    const unsigned char pinIn1M1_ = 17;
    const unsigned char pinIn2M1_ = 27;
    const unsigned char pinIn1M2_ = 18;
    const unsigned char pinIn2M2_ = 22;
    */
    const unsigned char pinIn1M3_ = 16;
    const unsigned char pinIn2M3_ = 25;
    // In1, In2 M4 on ioExpander

    // Config
    const unsigned int freq_ = 98000;

    // Functions
    void motMode_(const unsigned char motorNumber, const unsigned char mode);
};

#endif // TB6612FNG_H
