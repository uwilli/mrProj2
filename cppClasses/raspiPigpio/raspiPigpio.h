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
private:
    static int initialised_;
};

#endif // RASPIPIGPIO_H
