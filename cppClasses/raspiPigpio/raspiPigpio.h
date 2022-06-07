#ifndef RASPIPIGPIO_H
#define RASPIPIGPIO_H

#ifndef DAEMON
//#define DAEMON  // --> defined via .cmake file. Now defined here for recognition by Qt Creator
#endif

#ifndef ROS
//#define ROS  // --> defined via .cmake file. Now defined here for recognition by Qt Creator
#endif

#ifdef DAEMON
    #include "pigpiod_if2.h"
#else
    #include "pigpio.h"
#endif

#ifdef ROS
    #include <ros/console.h>
#else
    #include <iostream>
#endif

#include <stdexcept>


/**
 * @brief Parent class for pigpio c-Library functionality in cpp-Classes. To be inherited from.
 * @note Deamon must be used to run several programs with this or child classes simultaneously.
 */
class RaspiPigpio
{
public:
    RaspiPigpio();
    ~RaspiPigpio();
    void print(const std::string msg, const unsigned char rosLevel);
    void pinSetMode(const unsigned char bcmPin, const unsigned mode);
    void pinWrite(const unsigned char bcmPin, const bool level);
    bool pinRead(const unsigned char bcmPin);
    int getPi();

protected:
    void checkBcmPinValid_(const unsigned char bcmPin);
    int pi_ = 0; //which raspberry Pi

    const unsigned char ROS_DEBUG = 0;
    const unsigned char ROS_INFO = 1;
    const unsigned char ROS_WARN = 2;
    const unsigned char ROS_ERROR = 3;
    const unsigned char ROS_FATAL = 4;

private:
    static int initialised_;

};

#endif // RASPIPIGPIO_H
