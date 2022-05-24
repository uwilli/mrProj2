#ifndef PIGPIOPWM_H
#define PIGPIOPWM_H

#include "raspiPigpio.h"

class PigpioPwm : public RaspiPigpio
{
public:
    void initialise();
    void hardwarePwm(const unsigned char bcmPin, const unsigned int frequency, const uint32_t dutyCycle);
};

#endif // PIGPIOPWM_H
