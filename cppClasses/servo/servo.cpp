#include "servo.h"


/**
 * @brief Constructor needs a bcm pin for the servo. This pin cannot be changed once object created.
 * @param bcmPin: bcm pins 0-31 are allowed.
 * @param steeringServo: if 1, sets safe servo range for mrProj1 car (FHGR) and trimmed neutral.
 */
Servo::Servo(const unsigned char bcmPin, const bool steeringServo)
{
    bcmPin_ = bcmPin;

    if(steeringServo)
    {
        minMs_ = 900;
        maxMs_ = 1790;
        neutralMs_ = 1460;
    }

    softwareServo(bcmPin_, neutralMs_);
}


/**
 * @brief Constructor needs a bcm pin for the servo. This pin cannot be changed once object created.
 * @param bcmPin: bcm pins 0-31 are allowed.
 * @param neutralMs: Neutral position of servo in ms. Must be between minimum and maximum position. Is stored in object.
 * @param minMs: Minimum position of servo in ms. Is stored in object.
 * @param maxMs: Maximum position of servo in ms. Is stored in object.
 */
Servo::Servo(const unsigned char bcmPin, const unsigned int neutralMs, const unsigned int minMs, const unsigned int maxMs)
{
    bcmPin_ = bcmPin;

    setMinMs(minMs);
    setMaxMs(maxMs);
    setNeutralMs(neutralMs);

    softwareServo(bcmPin_, neutralMs_);
}


Servo::~Servo()
{
    softwareServo(bcmPin_, 0);
}


/**
 * @brief Move servo to a position.
 * @param ms: Dutycycle in ms of servo position.
 * @param cutToMinMax: Default=true.
 *                     If set to false, an error is thrown if ms is outside of programmed min/max positions.
 *                     If true, exceeding values are capped to min/max positions silently.
 */
void Servo::writeMs(const unsigned int ms, const bool cutToMinMax)
{
    unsigned int dutycycle = ms;

    if(cutToMinMax)
    {
        dutycycle = cutToMinMaxBoundaries_(ms);
    }
    else
    {
        checkMinMaxBoundaries_(ms);
    }

    softwareServo(bcmPin_, dutycycle);
}


/**
 * @brief set Servo to neutral position, as saved in object.
 */
void Servo::writeNeutral()
{
    softwareServo(bcmPin_, neutralMs_);
}


/**
 * @brief Set minimum allowed pulsewidth for servo.
 * @param minMs: Minimum allowed pulsewidth in ms. 500-2500. minMs must be smaller or equal maxMs.
 */
void Servo::setMinMs(const unsigned int minMs)
{
    checkMsStandardBoundaries_(minMs);

    if(minMs > maxMs_)
    {
        throw std::invalid_argument("Minimum dutycycle is bigger than maximum dutycycle");
    }

    minMs_ = minMs;
}


/**
 * @brief Set maximum allowed pulsewidth for servo.
 * @param maxMs: Maximum allowed pulsewidth in ms. 500-2500. maxMs must be greater or equal minMs.
 */
void Servo::setMaxMs(const unsigned int maxMs)
{
    checkMsStandardBoundaries_(maxMs);

    if(maxMs < minMs_)
    {
        throw std::invalid_argument("Maximum dutycycle is smaller than minimum dutycycle");
    }

    maxMs_ = maxMs;
}


/**
 * @brief Set neutral position of servo
 * @param neutralMs: Pulsewidth for neutral position in ms. Must be between minimum and maximum position.
 */
void Servo::setNeutralMs(const unsigned int neutralMs)
{
    checkMsStandardBoundaries_(neutralMs);

    if((neutralMs < minMs_) || (neutralMs > maxMs_))
    {
        throw std::invalid_argument("Neutral position must be between min and max values of servo.");
    }

    neutralMs_ = neutralMs;
}


/**
 * @brief Set minimum and maximum positions of servo.
 * @param minMs: Minimum allowed pulsewidth in ms. 500-2500. minMs must be smaller or equal maxMs.
 * @param maxMs: Maximum allowed pulsewidth in ms. 500-2500. maxMs must be greater or equal minMs.
 */
void Servo::setMinMaxMs(const unsigned int minMs, const unsigned int maxMs)
{
    setMinMs(minMs);
    setMaxMs(maxMs);
}


/**
 * @brief Set minimum, maximum and neutral position of servo.
 * @param minMs: Minimum allowed pulsewidth in ms. 500-2500. minMs must be smaller or equal maxMs.
 * @param maxMs: Maximum allowed pulsewidth in ms. 500-2500. maxMs must be greater or equal minMs.
 * @param neutralMs: Pulsewidth for neutral position in ms. Must be between minimum and maximum position.
 */
void Servo::setMinMaxNeutralMs(const unsigned int minMs, const unsigned int maxMs, const unsigned int neutralMs)
{
    setMinMs(minMs);
    setMaxMs(maxMs);
    setNeutralMs(neutralMs);
}


void Servo::checkMsStandardBoundaries_(const unsigned int val)
{
    if((val < 500) || (val > 2500))
    {
        throw std::invalid_argument("Servo pulse in ms must be between 500 and 2500");
    }
}

void Servo::checkMinMaxBoundaries_(const unsigned int dutycycle)
{
    if(dutycycle < minMs_)
    {
        throw std::invalid_argument("Servo dutycycle below programmed minimum position.");
    }

    if(dutycycle > maxMs_)
    {
        throw std::invalid_argument("Servo dutycycle above programmed maximum position.");
    }
}

unsigned int Servo::cutToMinMaxBoundaries_(const unsigned int dutycycle)
{
    unsigned int cut = dutycycle;

    if(dutycycle < minMs_)
    {
        cut = minMs_;
    }

    if(dutycycle > maxMs_)
    {
        cut = maxMs_;
    }

    return cut;
}
