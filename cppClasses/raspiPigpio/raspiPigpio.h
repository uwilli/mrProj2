#ifndef RASPIPIGPIO_H
#define RASPIPIGPIO_H

//#define DEAMON  // --> defined via .cmake file. Now defined here for recognition by Qt Creator

#ifdef DEAMON
    #include "pigpiod_if2.h"
#else
    #include "pigpio.h"
#endif

#include <stdexcept>


/**
 * @brief Parent class for pigpio c-Library functionality in cpp-Classes. To be inherited from.
 * @note Deamon must be used to run several programs with this or child classes simultaneously.
 */
class RaspiPigpio
{
public:
    RaspiPigpio();
    ~RaspiPigpio();
    void pinSetMode(const unsigned char bcmPin, const unsigned mode);
    void pinWrite(const unsigned char bcmPin, const bool level);
    bool pinRead(const unsigned char bcmPin);
    int getPi();

protected:
    void checkBcmPinValid_(const unsigned char bcmPin);
    int pi_ = 0; //which raspberry Pi

private:
    static int initialised_;

};

#endif // RASPIPIGPIO_H
