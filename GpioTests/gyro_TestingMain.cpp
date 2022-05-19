#include "lsm6ds33.h"
#include "unistd.h" // sleep

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
        std::cout << "Gyro : ";
        gyro.print();
        sens.getGyroData(gyro);
        std::cout << "Gyro : ";
        gyro.print();
        std::cout << "Acc : ";
        sens.getAccData(acc);
        acc.print();
        std::cout << "Acc : ";
        acc.print();
        sleep(1);
    }

    std::cout << "Reached end of main loop" << std::endl;
    return 0;
}
