#include "pigpioPwm.h"


/**
 * @brief Start Hardware frequency on allowed pins. Set dutycycle to 0 to stop hardware pwm.
 * @param bcmPin: BCM numbering! Possible pins: 12, 13, 18, 19
 * @param frequency: Frequency of hardware pwm. 0 (off) or 1-125M Hz.
 * @param dutyCycle: 0 (off) or to 1M (100%)
 */
void PigpioPwm::hardwarePwm(const unsigned char bcmPin, const unsigned int frequency, const uint32_t dutyCycle)
{
    int error = 0;

    error = gpioHardwarePWM(bcmPin, frequency, dutyCycle);
    if(error < 0)
    {
        switch (error) {
        case PI_BAD_GPIO:
        case PI_NOT_HPWM_GPIO:
            throw std::invalid_argument("Only bcm pins 12, 13, 18, 19 have hardware pwm capabilities.");
        case PI_BAD_HPWM_FREQ:
            throw std::invalid_argument("Hardware PWM frequency invalid");
        case PI_BAD_HPWM_DUTY:
            throw std::invalid_argument("Hardware PWM dutycycle not in 0-1M");
        default:
            throw std::runtime_error("Hardware PWM failed.");
        }
    }
}

/**
 * @brief Start/stop software pwm at 50Hz for servo operation.
 * @param bcmPin: bcm pins 0-31 are allowed.
 * @param pulsewidth: 0 to turn off, 500-2500 for operation. Careful, some servos have different end positions. Servos can be damaged if run over mechanical operating range.
 */
void PigpioPwm::softwareServo(const unsigned char bcmPin, const unsigned int pulsewidth)
{
    int error = 0;

    error = gpioServo(bcmPin, pulsewidth);
    if(error < 0)
    {
        switch (error) {
        case PI_BAD_USER_GPIO:
            throw std::invalid_argument("Invalid bcm pin for servo (software pwm).");
        case PI_BAD_PULSEWIDTH:
                throw std::invalid_argument("Servo pulsewidth must be between 500 and 2500, or 0 to turn off.");
        default:
            throw std::runtime_error("Software PWM for servo failed.");
        }
    }
}
