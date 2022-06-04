#ifndef PIGPIOPWM_H
#define PIGPIOPWM_H

#include "raspiPigpio.h"

class PigpioPwm : public RaspiPigpio
{
public:
    void hardwarePwm(const unsigned char bcmPin, const unsigned int frequency, const uint32_t dutyCycle);
    void softwareServo(const unsigned char bcmPin, const unsigned int pulsewidth);
};

#endif // PIGPIOPWM_H
