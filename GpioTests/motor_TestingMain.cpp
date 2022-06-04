#include "tb6612fng.h"
#include "unistd.h" // sleep
#include "iostream"

// NOTE: 100 percent power on motor can cause the pi to loose power and reboot

int main()
{
    Tb6612fng m3(3);

    std::cout << "forward" << std::endl;
    m3.speed(50);
    sleep(2);
    std::cout << "backward" << std::endl;
    m3.speed(-50);
    sleep(2);
    std::cout << "m3 off" << std::endl;
    m3.off();
    sleep(2);
    std::cout << "full power" << std::endl;
    m3.speed(100);
    sleep(2);
    std::cout << "off" << std::endl;
    m3.speed(0);
    sleep(2);
    std::cout << "-150" << std::endl;
    m3.speed(-150);
    sleep(2);
    m3.speed(100);
    std::cout << "1tf" << std::endl;
    sleep(2);

    std::cout << "off()" << std::endl;
    m3.off();
    sleep(2);
    std::cout << "wtf" << std::endl;

    return 0;
}
