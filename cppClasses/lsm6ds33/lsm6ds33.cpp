#include "lsm6ds33.h"


void Lsm6ds33::initialise()
{
    PigpioI2c::initialise();
    std::cout << "Gyro and accelerometer found." << std::endl;

    pushGyroMaxDPS_();
    pushGyroFreqMode_();
    pushAccMaxG_();
    pushAccFreqMode_();
}

/**
 * @brief Sets maximum degrees per second parameter on the gyroscope.
 * @param gyroMaxDPS: Sets value to nearest possible value:  125 dps
 *                                                         	 250 dps
 *                                                      	 500 dps
 *                                                         	1000 dps
 *                                                       	2000 dps
 * @return The value it chose to set the parameter to.
 */
unsigned int Lsm6ds33::setGyroMaxDPS(const unsigned int gyroMaxDPS)
{
    switch (gyroMaxDPS) { // implemented as switch, because vector etc would be overkill.
    case 0 ... 187:
        gyroMaxDPS_ = 125;
        break;
    case 188 ... 375:
        gyroMaxDPS_ = 250;
        break;
    case 376 ... 750:
        gyroMaxDPS_ = 500;
        break;
    case 751 ... 1500:
        gyroMaxDPS_ = 1000;
        break;
    default:
        gyroMaxDPS_ = 2000;
    }

    pushGyroMaxDPS_();
    return gyroMaxDPS_;
}

/**
 * @brief Sets data output frequency of Gyroscope.
 * @param gyroFreqMode: possible values:	0 --> Power Down
 * 												1 --> 12.5 Hz
 * 												2 --> 26 Hz
 * 												3 --> 52 Hz
 * 												4 --> 104 Hz
 * 												5 --> 208 Hz
 * 												6 --> 416 Hz
 * 												7 --> 833 Hz
 * 												8 --> 1660 Hz
 */
void Lsm6ds33::setGyroFreqMode(const unsigned char gyroFreqMode)
{
    if(gyroFreqMode > 8)
    {
        throw std::invalid_argument("Maximum Gyro Frequency mode is 8 (1660Hz).");
    }
    gyroFreqMode_ = gyroFreqMode;
    pushGyroFreqMode_();
}

/**
 * @brief Sets maximum g-Force parameter of accelerometer.
 * @param accMaxG: Chooses closest possible value :  2 g
 *                                                   4 g
 *                                                   8 g
 *                                                  16 g
 * @return The value the parameter was actually set to.
 */
unsigned char Lsm6ds33::setAccMaxG(const unsigned char accMaxG)
{
    switch (accMaxG) { // implemented as switch, because vector etc would be overkill.
    case 0 ... 2:
        accMaxG_ = 2;
        break;
    case 3 ... 5:
        accMaxG_ = 4;
        break;
    case 6 ... 11:
        accMaxG_ = 8;
        break;
    default:
        accMaxG_ = 16;
    }

    pushAccMaxG_();
    return accMaxG_;
}

/**
 * @brief Sets accelerometer data output frequency
 * @param accFreqMode: possible values :  0 --> Power Down
 *                                        1 --> 12.5
 *                                        2 --> 26 Hz
 *                                        3 --> 52 Hz
 *                                        4 --> 104 Hz
 *                                        5 --> 208 Hz
 *                                        6 --> 416 Hz
 *                                        7 --> 833 Hz
 *                                        8 --> 1660 Hz
 *                                        9 --> 3330 Hz
 *                                       10 --> 6660 Hz
 */
void Lsm6ds33::setAccFreqMode(const unsigned char accFreqMode)
{
    if(accFreqMode > 10)
    {
        throw std::invalid_argument("Maximum Accelerometer Frequency mode is 10 (6660Hz).");
    }
    accFreqMode_ = accFreqMode;
    pushAccFreqMode_();
}

/**
 * @brief Get gyro and acceleration data from sensor.
 *        Gyro in DPS (degrees per second)
 *        acceleration in g (9.81m/s^2)
 * @param &gyroData : gyro data written to this
 * @param &accData : acceleration data written to this
 */
void Lsm6ds33::getData(VecXYZ &gyroData, VecXYZ &accData)
{
    const unsigned char bytes = 12;
    char buf[bytes] = {};
    int temp = 0;
    float temp_float = 0;

    if(i2cReadI2CBlockData(i2cHandle_, dataReg_, buf, bytes) != bytes)
    {
        std::runtime_error("Could not read correct number (if any) of bytes from data register LSM6DS33.");
    }

    for(int i=0; i<5; i+=2)
    {
        // Gyro
        temp = (static_cast<unsigned int>(buf[i+1]) << 8) | buf[i];
        temp_float = (float) temp / 0x7FFF * gyroMaxDPS_ - calibGyro.getValAt(i/2); // divide by 2^15 (16bit is a 2 complement's), multiply by max value
        gyroData.setValAt(i/2, temp_float);

        // Acceleration
        temp = (static_cast<unsigned int>(buf[i+7]) << 8) | buf[i+6];
        temp_float = (float) temp / 0x7FFF * accMaxG_; // divide by 2^15 (16bit is a 2 complement's), multiply by max value
        accData.setValAt(i/2, temp_float);
    }
}

void Lsm6ds33::pushGyroMaxDPS_()
{
    unsigned char val = 0; // dps value we want to send
    char reg = 0; // data from and to register

    switch (gyroMaxDPS_) {
    case 125:
        val = 0x10;
        break;
    case 250:
        val = 0x00;
        break;
    case 500:
        val = 0x04;
        break;
    case 1000:
        val = 0x08;
        break;
    case 2000:
        val = 0x0C;
        break;
    default:
        throw std::invalid_argument("max degrees per second has an illegal value. Review setter Method guards.");
    }

    reg = i2cReadByteData(i2cHandle_, gyroSetupReg_); // Read register from sensor
    if(reg < 0)
    {
        throw std::runtime_error("Could not read gyroscope setup register.");
    }

    reg &= 0xF0; // set DPS bits to zero
    reg |= val;

    if(i2cWriteByteData(i2cHandle_, gyroSetupReg_, reg) < 0)
    {
        throw std::runtime_error("Could not write to gyroscope setup register.");
    }
}

void Lsm6ds33::pushGyroFreqMode_()
{
    char reg = 0;

    if(gyroFreqMode_ > 8)
    {
        throw std::invalid_argument("Gyroscope frequency mode is higher than 8 (max)");
    }

    reg = i2cReadByteData(i2cHandle_, gyroSetupReg_); // Read register from sensor
    if(reg < 0)
    {
        throw std::runtime_error("Could not read gyroscope setup register.");
    }

    reg &= 0x0F; // set freq bits to zero
    reg |= gyroFreqMode_ << 4;

    if(i2cWriteByteData(i2cHandle_, gyroSetupReg_, reg) < 0)
    {
        throw std::runtime_error("Could not write to gyroscope setup register.");
    }
}

void Lsm6ds33::pushAccMaxG_()
{
    unsigned char val = 0;
    char reg = 0;

    switch (accMaxG_) {
    case 2:
        val = 0x00;
        break;
    case 4:
        val = 0x08;
        break;
    case 8:
        val = 0x0C;
        break;
    case 16:
        val = 0x04;
        break;
    default:
        throw std::invalid_argument("max G has an illegal value. Review setter Method guards.");
    }

    reg = i2cReadByteData(i2cHandle_, accSetupReg_); // Read register from sensor
    if(reg < 0)
    {
        throw std::runtime_error("Could not read accelerometer setup register.");
    }

    reg &= 0xF3; // set freq bits to zero
    reg |= val;

    if(i2cWriteByteData(i2cHandle_, gyroSetupReg_, reg) < 0)
    {
        throw std::runtime_error("Could not write to accelerometer setup register.");
    }
}

void Lsm6ds33::pushAccFreqMode_()
{
    char reg = 0;

    if(accFreqMode_ > 10)
    {
        throw std::invalid_argument("Accelerometer frequency mode is higher than 10 (max)");
    }

    reg = i2cReadByteData(i2cHandle_, accSetupReg_); // Read register from sensor
    if(reg < 0)
    {
        throw std::runtime_error("Could not read accelerometer setup register.");
    }

    reg &= 0x0F; // set freq bits to zero
    reg |= accFreqMode_ << 4;

    if(i2cWriteByteData(i2cHandle_, accSetupReg_, reg) < 0)
    {
        throw std::runtime_error("Could not write to accelerometer setup register.");
    }
}





































