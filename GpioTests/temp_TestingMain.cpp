#include "mcp9808.h"
#include "unistd.h"

int main()
{
    Mcp9808 sens;
    sens.initialise();
    sleep(1);
    sens.printConfig();
    for(int i=0; i<10; i++)
    {
        sens.readTemperature();
        sleep(2);
    }
    std::cout << "Reached end of main loop" << std::endl;
    return 0;
}
