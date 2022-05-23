#include "lsm6ds33.h"
#include "unistd.h" // sleep

#include "pca9554b.h"

int main()
{
    PigpioI2c::i2cScanner();

    Pca9554b expander;
    expander.initialise();

    expander.allOff();

    sleep(3);
    return 0;
}
