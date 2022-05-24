#include "lsm6ds33.h"
#include "unistd.h" // sleep

#include "pca9554b.h"

int main()
{
    PigpioI2c::i2cScanner();

    Pca9554b exp;
    exp.initialise();

    exp.allOff();
    sleep(1);
    exp.ledFront(1);
    sleep(1);
    exp.ledFront(0);
    sleep(1);
    exp.ledRear(1);
    sleep(1);
    exp.ledRear(0);
    sleep(2);
    for(int i=0; i<4; i++)
    {
        exp.ledSet(0x01 << i);
        usleep(500000);
    }
    exp.ledAll(0);
    sleep(1);
    exp.ledAll(1);
    sleep(1);
    exp.ledAll(0);
    sleep(3);
    return 0;
}
