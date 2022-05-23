#include "lsm6ds33.h"

/**
 * @brief Initialises sensor and parent class. IMU does is powered off without initialisation.
 */
void Lsm6ds33::initialise()
{
    PigpioI2c::initialise();
    std::cout << "Gyro and accelerometer found." << std::endl;

    pushGyroMaxDPS_();
    pushGyroFreqMode_();
    pushAccMaxG_();
    pushAccFreqMode_();
    pushAccAntiAliasingMode_();
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
 * @brief Set aliasing Filter on the Accelerometer.
 * @param accAntiAliasingMode: possible values : 0 --> 400 Hz
 *                                               1 --> 200 Hz
 *                                               2 --> 100 Hz
 *                                               3 -->  50 Hz
 */
void Lsm6ds33::setAccAntiAliasingMode(const unsigned char accAntiAliasingMode)
{
    if(accAntiAliasingMode > 3)
    {
        throw std::invalid_argument("Maximum Anti-Aliasing Mode is 3 (50Hz). Max Frequency is 400Hz (Mode 0).");
    }
    accAntiAliasingMode_ = accAntiAliasingMode;
    pushAccAntiAliasingMode_();
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
    // Copy paste code and adapted to optimise speed (instead of calling i2cRead twice for both data sets
    const unsigned char bytes = 12;
    char buf[bytes] = {};
    float temp_float = 0;

    if(pollStatReg_)
    {
        pollStatRegLoop_(3);
    }

    readI2cBlockData(dataReg_, buf, bytes);

    for(int i=0; i<5; i+=2)
    {
        // Gyro
        temp_float = lE2BytesToFloat_(buf, i) / 0x7FFF * gyroMaxDPS_ - calibGyro_.getValAt(i/2); // divide by 2^15 (16bit is a 2 complement's), multiply by max value -> like percent
        gyroData.setValAt(i/2, temp_float);

        // Acceleration
        temp_float = lE2BytesToFloat_(buf, i+6) / 0x7FFF * accMaxG_;
        accData.setValAt(i/2, temp_float);
    }
}

/**
 * @brief Get only gyro data
 *        Gyro in DPS (degrees per seconds)
 * @param gyroData : parameter to be written to.
 */
void Lsm6ds33::getGyroData(VecXYZ &gyroData)
{
    const unsigned char bytes = 6;
    char buf[bytes] = {};
    float temp_float = 0;

    if(pollStatReg_)
    {
        pollStatRegLoop_(1);
    }

    readI2cBlockData(dataReg_, buf, bytes);

    for(int i=0; i<5; i+=2)
    {
        // Gyro
        temp_float = lE2BytesToFloat_(buf, i) / 0x7FFF * gyroMaxDPS_ - calibGyro_.getValAt(i/2); // divide by 2^15 (16bit is a 2 complement's), multiply by max value -> like percent
        gyroData.setValAt(i/2, temp_float);
    }
}

/**
 * @brief Get only acc data
 *        acceleration in g (9.81m/s^2)
 * @param accData : parameter to be written to.
 */
void Lsm6ds33::getAccData(VecXYZ &accData)
{
    const unsigned char accReg = dataReg_ + 6;
    const unsigned char bytes = 6;
    char buf[bytes] = {};
    float temp_float = 0;

    if(pollStatReg_)
    {
        pollStatRegLoop_(0);
    }

    readI2cBlockData(accReg, buf, bytes);

    for(int i=0; i<5; i+=2)
    {
        // Acceleration
        temp_float = lE2BytesToFloat_(buf, i) / 0x7FFF * accMaxG_;
        accData.setValAt(i/2, temp_float);
    }
}

/**
 * @brief Takes several measurements to calibrate the gyro. DO NOT MOVE DEVICE WHILE CALIBRATING.
 */
void Lsm6ds33::calibrate()
{
    VecXYZ sum;
    VecXYZ current;

    std::cout << "Using unistd.h, adapt for ROS!" << std::endl;
    std::cout << "Don't move! Calibrating ... " << std::flush;

    for(unsigned int i=0; i<calibrateCycles_; i++)
    {
        getGyroData(current);
        for(int i=0; i<3; i++)
        {
            sum.setValAt(i, sum.getValAt(i) + current.getValAt(i));
        }
        usleep(100000); // CHANGE THIS FOR ROS
    }

    std::cout << "Done." << std::flush << std::endl;

    for(int i=0; i<3; i++)
    {
        calibGyro_.setValAt(i, sum.getValAt(i) / calibrateCycles_ + calibGyro_.getValAt(i));
    }
}

/**
 * @brief Takes several measurements to calibrate the gyro. DO NOT MOVE DEVICE WHILE CALIBRATING.
 * @param cycles : Number of measurements that the average is taken from.
 */
void Lsm6ds33::calibrate(const unsigned int cycles)
{
    unsigned old = 0;
    old = calibrateCycles_;
    calibrateCycles_ = cycles;
    calibrate();
    calibrateCycles_ = old;
}

/**
 * @brief Set the default number of cycles that are done while calibrating
 * @param cycles : Number of cycles
 */
void Lsm6ds33::setDefaultCalibrateCycles(const unsigned int cycles)
{
    calibrateCycles_ = cycles;
}

/**
 * @brief Enable status register polling for availability of new values for a maximum of cycles set with setStatRegMaxLoops.
 * @param pollStatReg set True for polling.
 */
void Lsm6ds33::setPollStatReg(const bool pollStatReg)
{
    pollStatReg_ = pollStatReg;
}

/**
 * @brief Set how many loops are in maximum polled before throwing error. Enable Polling with setPollStatReg.
 * @param statRegMaxPollingLoops : Maximum number of polling loops. Set to -1 for infinite polling.
 */
void Lsm6ds33::setStatRegMaxLoops(const int statRegMaxPollingLoops)
{
    statRegMaxLoops_ = statRegMaxPollingLoops;
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

    reg = readByteData(gyroSetupReg_);

    reg &= 0xF0; // set DPS bits to zero
    reg |= val;

    writeByteData(gyroSetupReg_, reg);
}

void Lsm6ds33::pushGyroFreqMode_()
{
    char reg = 0;

    if(gyroFreqMode_ > 8)
    {
        throw std::invalid_argument("Gyroscope frequency mode is higher than 8 (max)");
    }

    reg = readByteData(gyroSetupReg_);

    reg &= 0x0F; // set freq bits to zero
    reg |= gyroFreqMode_ << 4;

    writeByteData(gyroSetupReg_, reg);
}

void Lsm6ds33::pushAccMaxG_()
{
    unsigned char val = 0;
    char reg = 0;

    switch (accMaxG_) {
    case 2:
        val = 0x00 << 2;
        break;
    case 4:
        val = 0x02 << 2;
        break;
    case 8:
        val = 0x03 << 2;
        break;
    case 16:
        val = 0x01 << 2;
        break;
    default:
        throw std::invalid_argument("max G has an illegal value. Review setter Method guards.");
    }

    reg = readByteData(accSetupReg_);

    reg &= 0xF3; // set acc bits to zero
    reg |= val;

    writeByteData(accSetupReg_, reg);
}

void Lsm6ds33::pushAccFreqMode_()
{
    char reg = 0;

    if(accFreqMode_ > 10)
    {
        throw std::invalid_argument("Accelerometer frequency mode is higher than 10 (max)");
    }

    reg = readByteData(accSetupReg_);

    reg &= 0x0F; // set freq bits to zero
    reg |= accFreqMode_ << 4;

    writeByteData(accSetupReg_, reg);
}

void Lsm6ds33::pushAccAntiAliasingMode_()
{
    char reg = 0;

    switch (accAntiAliasingMode_) {
    case 0:
        break; // 400Hz
    case 1:
        break; // 200Hz
    case 2:
        break; // 100Hz
    case 3:
        break; // 50Hz
    default:
        throw std::invalid_argument("Anti-aliasing mode has an illegal value. Review setter Method guards.");
    }

    reg = readByteData(accSetupReg_);

    // Anti-aliasing filter to 50 Hz :
    reg &= 0xFC;
    reg |= accAntiAliasingMode_;

    writeByteData(accSetupReg_, reg);
}

/**
 * @brief Converts a 2 byte two's complement char string to a float
 * @param buf : Buffer where char string is stored. Little Endian.
 * @param index : index = LSB, index+1 = MSB
 * @return converted value as float
 */
float Lsm6ds33::lE2BytesToFloat_(const char* buf, const unsigned int index)
{
    int temp = 0;
    temp = (static_cast<unsigned int>(buf[index+1]) << 8) | buf[index];

    if((temp >>15)  & 0x1) // negative number
    {
        temp -= 0xFFFF + 1; // '~val + 1' did not work, 230 became -230
    }

    return (float) temp;
}

/**
 * @brief Polls status registers until new values are available. Max polling cycles can be set via Config variables.
 * @param whichSens: possible values : 0 --> Accelerometer
 *                                     1 --> Gyroscope
 *                                     3 --> Accelerometer and Gyro
 */
void Lsm6ds33::pollStatRegLoop_(const unsigned char whichSens)
{
    unsigned char whichBits = 0;
    char polling = 0;
    int loops = 0;
    bool infiniteLoop = false;

    switch (whichSens) {
    case 0:
        whichBits = 0x00;
        break;
    case 1:
        whichBits = 0x01;
        break;
    case 3:
        whichBits = 0x03;
        break;
    default:
        throw std::invalid_argument("Either invalid Status register bit or these bits are not yet implemented.");
    }

    if(statRegMaxLoops_ == -1)
    {
        infiniteLoop = true;
    }

    do
    {
        loops++;
        polling = readByteData(statReg_);

        if((loops > statRegMaxLoops_) && (infiniteLoop == false))
        {
            throw std::runtime_error("Polled status register more than maximum allowed times, check refresh rates.");
        }
    } while((polling & whichBits) != whichBits);
}



































