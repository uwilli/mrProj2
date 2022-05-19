#include "lsm6ds33.h"
#include "unistd.h"

int main()
{
    VecXYZ gyro;
    VecXYZ acc;

    PigpioI2c::i2cScanner();
    sleep(1);
    Lsm6ds33 sens;
    sens.initialise();
    sleep(1);
    sens.calibrate();

    for(int i=0; i<10; i++)
    {
        sens.getData(gyro, acc);
        gyro.print();
        acc.print();
    }

    std::cout << "Reached end of main loop" << std::endl;
    return 0;
}
