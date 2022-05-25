#ifndef LSM6DS33_H
#define LSM6DS33_H

#include "pigpioI2c.h"
#include "vecXYZ.h"
#include "unistd.h"

/**
 * @brief The Lsm6ds33 class creates a cpp interface for the gyroscope and magnetic sensor LSM6DS33 for raspberry Pi.
 * @note The i2c interface must be enabled and configured on the raspberry pi.
 * @author Urban Willi. Adapted from Jan Schuessler, FHGR Mobile Robotics Project 1 semester 3.
 */
class Lsm6ds33 : public PigpioI2c
{
public:
    Lsm6ds33();
    unsigned int setGyroMaxDPS(const unsigned int gyroMaxDPS); // rounds them to nearest possible value and returns chosen one.
    void setGyroFreqMode(const unsigned char gyroFreqMode);
    unsigned char setAccMaxG(const unsigned char accMaxG);
    void setAccFreqMode(const unsigned char accFreqMode);
    void setAccAntiAliasingMode(const unsigned char accAntiAliasingMode);
    void getData(VecXYZ &gyroData, VecXYZ &accData);
    void getGyroData(VecXYZ &gyroData);
    void getAccData(VecXYZ &accData);
    void calibrate();
    void calibrate(const unsigned int cycles);
    void setDefaultCalibrateCycles(const unsigned int cycles);
    void setPollStatReg(const bool pollStatReg);
    void setStatRegMaxLoops(const int statRegMaxPollingLoops);

private:
    // Registers
    const char gyroSetupReg_ = 0x11;
    const char accSetupReg_ = 0x10;
    const char statReg_ = 0x1E;
    const char dataReg_ = 0x22; // gyro: 0x22-0x27, acc: 0x28-0x2D

    // Config
    bool pollStatReg_ = 0; // only for debugging, standard = 1
    int statRegMaxLoops_ = 50; // -1 for infinite polling
    unsigned int gyroMaxDPS_ = 500; // degrees per second
    unsigned char gyroFreqMode_ = 1; // 12.5Hz
    unsigned char accFreqMode_ = 1; // 12.5Hz
    unsigned char accMaxG_ = 4;
    unsigned char accAntiAliasingMode_ = 0; // 400Hz

    // Functions
    void pushGyroMaxDPS_();
    void pushGyroFreqMode_();
    void pushAccMaxG_();
    void pushAccFreqMode_();
    void pushAccAntiAliasingMode_();
    float lE2BytesToFloat_(const char* buf, const unsigned int index);
    void pollStatRegLoop_(const unsigned char whichSens); // 0 = Accelerometer, 1 = Gyro, 3 = Accelerometer & Gyro.

    // Variables
    VecXYZ calibGyro_;
    unsigned int calibrateCycles_ = 50;
};

#endif // LSM6DS33_H
