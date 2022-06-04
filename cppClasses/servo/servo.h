#ifndef SERVO_H
#define SERVO_H

#include "pigpioPwm.h"

/**
 * @brief Easy implementation of a servo as an object, can store min and max allowes values for positions.
 * @note Time must be given for servo to move before ending programm/destructing object.
 */
class Servo : PigpioPwm
{
public:
    Servo(const unsigned char bcmPin, const bool steeringServo=false);
    Servo(const unsigned char bcmPin, const unsigned int neutralMs, const unsigned int minMs, const unsigned int maxMs);
    ~Servo();

    void writeMs(const unsigned int ms, const bool cutToMinMax=true);
    void writeNeutral();

    void setMinMs(const unsigned int minMs);
    void setMaxMs(const unsigned int maxMs);
    void setNeutralMs(const unsigned int neutralMs);
    void setMinMaxMs(const unsigned int minMs, const unsigned int maxMs);
    void setMinMaxNeutralMs(const unsigned int minMs, const unsigned int maxMs, const unsigned int neutralMs);
    unsigned int getMinMs();
    unsigned int getMaxMs();
    unsigned int getNeutralMs();
    unsigned char getBcmPin();

private:
    unsigned char bcmPin_;
    unsigned int neutralMs_ = 1500;
    unsigned int minMs_ = 500;
    unsigned int maxMs_ = 2500;
    void checkMsStandardBoundaries_(const unsigned int val);
    void checkMinMaxBoundaries_(const unsigned int dutycycle);
    unsigned int cutToMinMaxBoundaries_(const unsigned int dutycycle);

};

#endif // SERVO_H
