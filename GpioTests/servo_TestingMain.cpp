#include "tb6612fng.h"
#include "unistd.h" // sleep
#include "iostream"

int main()
{
    Tb6612fng mot;

    std::cout << "forward" << std::endl;
    mot.m3(50);
    sleep(2);
    std::cout << "backward" << std::endl;
    mot.m3(-50);
    sleep(2);
    std::cout << "All off" << std::endl;
    mot.allOff();
    sleep(2);
    std::cout << "full power" << std::endl;
    mot.m3(100);
    sleep(2);
    std::cout << "off" << std::endl;
    mot.m3(0);
    sleep(2);
    std::cout << "150" << std::endl;
    mot.m3(150);

    return 0;
}
