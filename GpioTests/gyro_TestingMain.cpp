#include "lsm6ds33.h"
#include "unistd.h"

int main()
{
    PigpioI2c::i2cScanner();
    sleep(1);
    Lsm6ds33 sens;
    sens.initialise();
    sleep(1);
    int ret = sens.setGyroMaxDPS(612);
    std::cout << ret << " returnvalue" << std::endl;

    std::cout << "Reached end of main loop" << std::endl;
    return 0;
}
