#include "servo.h"
#include "pca9554b.h"
#include "unistd.h" // sleep
#include "iostream"

int main()
{
    Pca9554b ioExp;
    ioExp.allOff();

    Servo stServo(13, true);

    stServo.writeMs(0);
    sleep(1);
    stServo.writeMs(3000);
    sleep(1);

    stServo.writeMs(950);

    sleep(2);

    stServo.writeNeutral();

    std::cout << "set to neutral" << std::endl;
    sleep(2);
    return 0;
}
