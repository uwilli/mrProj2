#include <iostream>
#include "pigpio.h"

int main()
{
    if(gpioInitialise() < 0)
    {
        std::cout << "Initialise failed" << std::endl;
        return -1;
    }
    std::cout << "HelloWorld_cpp" << std::endl;

    return 0;
}
