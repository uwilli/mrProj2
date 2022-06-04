#ifndef TB6612FNG_H
#define TB6612FNG_H

#include "pigpioPwm.h"


/**
 * @brief Motor driver for TB6612FNG installed on mrProj1 FHGR PCB.
 * @note Only motor 3 implemented.
 * @note Brownout can occur with high motor currents!
 */
class Tb6612fng : public PigpioPwm
{
public:
    Tb6612fng(const unsigned char motorNumber);
    ~Tb6612fng();
    static void allOff();
    void speed(const int percent);
    void off();

private:
    unsigned char pinIn1_;
    unsigned char pinIn2_;
    unsigned char pinPwm_;

    // Config
    const unsigned int freq_ = 98000;
};

#endif // TB6612FNG_H
