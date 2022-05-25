#include "pigpioI2c.h"


/**
 * @brief Constructor, address cannot be changed once object is initialised. Default bus on raspberry pi = 1.
 * @param i2cAddr: i2c-Address of device in 8bit-format (shifted internally)
 */
PigpioI2c::PigpioI2c(const unsigned char i2cAddr)
{
    i2cAddr_ = i2cAddr;
    initialise_();
}


/**
 * @brief Constructor, address cannot be changed once object is initialised.
 * @param i2cAddr: i2c-Address of device in 8bit-format (shifted internally)
 * @param i2cBus: Bus on raspberry pi.
 */
PigpioI2c::PigpioI2c(const unsigned char i2cAddr, const unsigned char i2cBus)
{
    i2cAddr_ = i2cAddr;
    i2cBus_ = i2cBus;
    initialise_();
}


PigpioI2c::~PigpioI2c()
{
    i2cClose(i2cHandle_);
}


/**
 * @brief Scan for i2c-devices on default bus 1 of raspberry pi. Print list of found devices to console.
 */
void PigpioI2c::i2cScanner()
{
    i2cScanner(1); // standard i2c bus Raspi is 1
}


/**
 * @brief Scan for i2c-devices on selected bus on raspberry pi. Print list of found devices.
 * @param i2cBus: target i2c-Bus of raspberry pi.
 */
void PigpioI2c::i2cScanner(const unsigned char i2cBus)
{
    bool noDevice = true;
    RaspiPigpio bus;

    int i2c_handle;
    for(int i=1; i<128; i++)
    {
        // changed to 7bit address inside of function!
        i2c_handle = i2cOpen(i2cBus, i, 0); // Last argument must always be zero, i2c flags not currently not defined.
        if(i2c_handle >= 0)
        {
            if(i2cWriteByte(i2c_handle, 0) >= 0)
            {
                noDevice = false;
                printf("I2C device at address 0x%02X\n", i);
                i2cClose(i2c_handle);
            }
        }
    }

    if(noDevice)
    {
        std::cout << "No i2c-devices found on bus " << i2cBus << "." << std::endl;
    }
}


/**
 * @brief Returns i2c-bus of raspberryPi, for which the device is set up.
 * @return i2c-Bus of Raspberry-pi
 */
unsigned char PigpioI2c::getI2cBus()
{
    return i2cBus_;
}


/**
 * @brief Get i2c-Address associated with object.
 * @return i2c Address
 */
unsigned char PigpioI2c::getI2cAddr()
{
    return i2cAddr_;
}


/**
 * @brief Read 1 byte of data from specified register.
 * @param reg : Register address to be read from on the i2c-device.
 * @return Content of register at specified adress.
 */
unsigned char PigpioI2c::readByteData(const unsigned char reg)
{
    char regByte = -1;

    regByte = i2cReadByteData(i2cHandle_, reg);

    if(reg < 0)
    {
        throw std::runtime_error("Could not read register from i2c-device.");
    }

    return regByte;
}


/**
 * @brief Read a word (16bit) from register.
 * @param reg: Address of register on i2c-device
 * @return Word read from register.
 */
unsigned int PigpioI2c::readWordData(const unsigned char reg)
{
    int data = 0;

    data = i2cReadWordData(i2cHandle_, reg);
    if(data < 0)
    {
        throw std::runtime_error("Could not read word from register in i2c-device.");
    }

    return data;
}


/**
 * @brief Read bytes number of bytes data from register, starting from adress reg, into buffer.
 * @param reg: Address of first byte
 * @param buffer: Array that contents will be stored to.
 * @param bytes: number of bytes to be read consecutevely.
 */
void PigpioI2c::readI2cBlockData(const unsigned char reg, char* buffer, const unsigned int bytes)
{
    if(i2cReadI2CBlockData(i2cHandle_, reg, buffer, bytes) != static_cast<char>(bytes))
    {
        std::runtime_error("Could not read correct number (if any) of bytes from i2c-register.");
    }
}


/**
 * @brief Write 1 byte of data to specified adress on i2c-device.
 * @param reg: Address to be written to.
 * @param byte: byte to be written.
 */
void PigpioI2c::writeByteData(const unsigned char reg, const unsigned char byte)
{
    if(i2cWriteByteData(i2cHandle_, reg, byte) < 0)
    {
        throw std::runtime_error("Could not write to register of i2c-device.");
    }
}


/**
 * @brief Write a word to the specified register.
 * @param reg: Address of register to be written to.
 * @param word: 16bit word to be written to i2c-device.
 */
void PigpioI2c::writeWordData(const unsigned char reg, const unsigned int word)
{
    if(i2cWriteWordData(i2cHandle_, reg, word) < 0)
    {
        throw std::runtime_error("Writing to config register of MCP9808 failed.");
    }
}


/**
 * @brief initialises i2c-Device with address specified in constructor. Must be called before utilizing any other functions (except i2c-Scanner).
 */
void PigpioI2c::initialise_()
{
    char i2cHandle = -1;

    i2cHandle = i2cOpen(i2cBus_, i2cAddr_, 0); // Last argument must always be zero, i2c flags not currently not defined in pigpio.
    if(i2cHandle < 0)
    {
        throw std::runtime_error("Failed to open i2c communication. (i2cOpen() pigpio)");
    }

    if(i2cWriteByte(i2cHandle, 0) < 0)
    {
        i2cClose(i2cHandle);
        printf("No device found at address : 0x%02X\n", i2cAddr_);
        fflush(stdout);
        throw std::runtime_error("No device found at specified i2c-Address.");
    }
    else
    {
        i2cHandle_ = i2cHandle;
        std::cout << "Device is here and working." << std::endl;
    }
}



