#include <stdio.h>
#include <unistd.h>
#include "pigpio.h"


int main()
{
    if (gpioInitialise() < 0)
    {
        printf("Failure...\n");
        return -1;
    }

    int sensorHandle = i2cOpen(1, 0x18, 0);
    if (sensorHandle < 0)
    {
        printf("Error to open I2c-Bus\n");
        return -1;
    }

    i2cWriteWordData(sensorHandle, 0x01, 0);
    sleep(1);

    while (1)
    {
        int v = i2cReadWordData(sensorHandle, 0x05);
        int val = ((v << 8) | (v >> 8)) & 0x1FFF;
        if(val > 4095)
        {
            val -= 8192;
        }
        float cTemp = val * 0.0625;
        printf("Temperature : %f\n", cTemp);
        sleep(1);
    }

    i2cClose(sensorHandle);
    gpioTerminate();
    return 0;
}
