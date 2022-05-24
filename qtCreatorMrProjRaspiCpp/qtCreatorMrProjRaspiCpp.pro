TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../GpioTests/gyro_TestingMain.cpp \
    ../GpioTests/ioExp_TestingMain.cpp \
    ../GpioTests/motor_TestingMain.cpp \
    ../GpioTests/temp_DemoMcp9808.cpp \
    ../GpioTests/temp_TestingMain.cpp \
    ../cppClasses/lsm6ds33/lsm6ds33.cpp \
    ../cppClasses/mcp9808/mcp9808.cpp \
    ../cppClasses/pca9554b/pca9554b.cpp \
    ../cppClasses/pigpioI2c/pigpioI2c.cpp \
    ../cppClasses/pigpioPwm/pigpioPwm.cpp \
    ../cppClasses/raspiPigpio/raspiPigpio.cpp \
    ../cppClasses/tb6612fng/tb6612fng.cpp \
    ../cppClasses/vecXYZ/vecXYZ.cpp

HEADERS += \
    ../cppClasses/lsm6ds33/lsm6ds33.h \
    ../cppClasses/mcp9808/mcp9808.h \
    ../cppClasses/pca9554b/pca9554b.h \
    ../cppClasses/pigpioI2c/pigpioI2c.h \
    ../cppClasses/pigpioPwm/pigpioPwm.h \
    ../cppClasses/raspiPigpio/raspiPigpio.h \
    ../cppClasses/tb6612fng/tb6612fng.h \
    ../cppClasses/vecXYZ/vecXYZ.h

INCLUDEPATH += \
    ../cppClasses/lsm6ds33 \
    ../cppClasses/mcp9808 \
    ../cppClasses/pca9554b \
    ../cppClasses/tb6612fng \
    ../cppClasses/pigpioI2c \
    ../cppClasses/pigpioPwm \
    ../cppClasses/raspiPigpio \
    ../cppClasses/vecXYZ
