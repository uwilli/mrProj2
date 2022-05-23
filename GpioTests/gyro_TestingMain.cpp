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
    /*
    sleep(1);
    //sens.calibrate();

    for(int i=0; i<10; i++)
    {
        sens.getData(gyro, acc);
        std::cout << std::endl; //"Gyro : ";
        //gyro.print();
        //sens.getGyroData(gyro);
        //std::cout << "Gyro : ";
        //gyro.print();
        std::cout << "Acc : ";
        acc.print();
        sens.getAccData(acc);
        std::cout << "Acc : ";
        acc.print();
        sleep(1);


    }
    */
    float testfloat = -0.13;
    int testint = static_cast<unsigned int>(3);
    testint = ~testint + 1;

    char buffer[4] = {static_cast<char>(0x09), static_cast<char>(0x40), static_cast<char>(0xFF), static_cast<char>(0xFF)};
    std::cout << "PF test      " << ~static_cast<unsigned char>(buffer[3])+1 << std::endl;
    float pos = sens.lE2BytesToFloat_(buffer, 0)/0x7fff*2;
    std::cout << "+:   " << pos << std::endl;
    float neg = sens.lE2BytesToFloat_(buffer, 2)/0x7fff*2;

    std::cout << "-:   " << neg << std::endl;

    std::cout << "Reached end of main loop" << std::endl;
    return 0;
}
