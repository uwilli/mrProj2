#include "mcp9808.h"


void Mcp9808::initialise()
{
    PigpioI2c::initialise();
}

void Mcp9808::initialise(bool initialiseRaspiPigpio)
{
    initialiseRaspiPigpio_ = initialiseRaspiPigpio;
    initialise();
}
