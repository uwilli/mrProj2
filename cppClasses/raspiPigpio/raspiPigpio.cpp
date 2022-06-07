#include "raspiPigpio.h"


int RaspiPigpio::initialised_ = 0;

/**
 * @brief initialise pigpio library.
 */
RaspiPigpio::RaspiPigpio::RaspiPigpio()
{
    if(initialised_ < 1)
    {
#ifdef DAEMON
        pi_ = pigpio_start(nullptr, nullptr); //default is localhost, port 8888
        if(pi_ < 0)
        {
            throw std::runtime_error("Could not connect to pigpiod (DAEMON).");
        }
#else
        if(gpioInitialise() < 0)
        {
            throw std::runtime_error("Pigpio gpioInitialise() failed.");
        }
#endif
    }
    initialised_ ++;
}


RaspiPigpio::~RaspiPigpio()
{
    initialised_ --;

    if(initialised_ < 1)
    {
#ifdef DAEMON
        pigpio_stop(pi_);
#else
        gpioTerminate();
#endif
        initialised_ = 0;
    }
}

/**
 * @brief Print message to correct ros log level or std::cout if ROS is not defined.
 * @param msg: String to be printed
 * @param rosLevel: Possible values: 0 --> Debug    Ignored when ROS not defined
 *                                   1 --> Info
 *                                   2 --> Warn
 *                                   3 --> Error
 *                                   4 --> Fatal
 */
void RaspiPigpio::print(const std::string msg, const unsigned char rosLevel)
{
#ifdef ROS
    switch(rosLevel)
    {
    case 0:
        ROS_DEBUG_STREAM(msg);
        break;
    case 1:
        ROS_INFO_STREAM(msg);
        break;
    case 2:
        ROS_WARN_STREAM(msg);
        break;
    case 3:
        ROS_ERROR_STREAM(msg);
        break;
    case 4:
        ROS_FATAL_STREAM(msg);
        break;
    default:
        throw std::invalid_argument("ROS debug level invalid argument, allowed 0-4");
    }
#else
    std::cout << msg << std::endl;
#endif
}


/**
 * @brief Set mode of gpioPin.
 * @param bcmPin: Gpio concerned, BCM numbering!
 * @param mode: mode 0-7, use constants defined in library, PI_INPUT, PI_OUTPUT ...
 */
void RaspiPigpio::pinSetMode(unsigned char bcmPin, unsigned mode)
{
    checkBcmPinValid_(bcmPin);

#ifdef DAEMON
    if(set_mode(pi_, bcmPin, mode) < 0)
#else
    if(gpioSetMode(bcmPin, mode) < 0)
#endif
    {
        throw std::runtime_error("Could not set mode of gpio pin");
    }

}


/**
 * @brief Write low or High to pin set to Output mode.
 * @param bcmPin: Gpio concerned, BCM numbering!
 * @param level: 1 --> HIGH, 0 --> LOW
 */
void RaspiPigpio::pinWrite(const unsigned char bcmPin, const bool level)
{
    checkBcmPinValid_(bcmPin);

#ifdef DAEMON
    if(gpio_write(pi_, bcmPin, level) < 0)
#else
    if(gpioWrite(bcmPin, level) < 0)
#endif
    {
        throw std::runtime_error("Could not write level to gpio pin");
    }
}


/**
 * @brief Read level of pin set to input
 * @param bcmPin: Gpio concerned, BCM numbering!
 * @return level: 1 --> HIGH, 0 --> LOW
 */
bool RaspiPigpio::pinRead(const unsigned char bcmPin)
{
    int level = 0;

    checkBcmPinValid_(bcmPin);

#ifdef DAEMON
    level = gpio_read(pi_, bcmPin);
#else
    level = gpioRead(bcmPin);
#endif
    if(level < 0)
    {
        throw std::runtime_error("Could not read level of gpio pin");
    }

    return level;
}


/**
 * @brief Get internal handle which pi the pigpio DAEMON is running on.
 * @return pi: 0 if DAEMON is undefined, pi_ otherwise.
 */
int RaspiPigpio::getPi()
{
    return pi_;
}


void RaspiPigpio::checkBcmPinValid_(const unsigned char bcmPin)
{
    bool valid = true;

    if(bcmPin == 0)
    {
        valid = false;
    }
    if(bcmPin > 27)
    {
        valid = false;
    }

    if(!valid)
    {
        throw std::invalid_argument("BCM-pin does not exist. Must be between 1 and 27.");
    }
}
