#ifndef RASPIPIGPIO_H
#define RASPIPIGPIO_H

#include "pigpio.h"

#include <stdexcept>


/**
 * @brief Parent class for pigpio c-Library functionality in cpp-Classes. To be inherited from.
 */
class RaspiPigpio
{
public:
    ~RaspiPigpio();
    void initialise();
    void pinSetMode(const unsigned char bcmPin, const unsigned mode);
    void pinWrite(const unsigned char bcmPin, const bool level);
    bool pinRead(const unsigned char bcmPin);

protected:
    void checkBcmPinValid_(const unsigned char bcmPin);

private:
    static int initialised_;

};

#endif // RASPIPIGPIO_H
