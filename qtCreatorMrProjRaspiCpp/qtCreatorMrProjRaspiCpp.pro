TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../GpioTests/temp_DemoMcp9808.cpp \
    ../GpioTests/temp_TestingMain.cpp \
    ../cppClasses/i2cScanner/i2cscanner.cpp \
    ../cppClasses/mcp9808/mcp9808.cpp \
    ../cppClasses/pigpioI2c/pigpioI2c.cpp \
    ../cppClasses/raspiPigpio/raspiPigpio.cpp

HEADERS += \
    ../cppClasses/i2cScanner/i2cscanner.h \
    ../cppClasses/mcp9808/mcp9808.h \
    ../cppClasses/pigpioI2c/pigpioI2c.h \
    ../cppClasses/raspiPigpio/raspiPigpio.h

INCLUDEPATH += \
    ../cppClasses/mcp9808 \
    ../cppClasses/pigpioI2c \
    ../cppClasses/raspiPigpio
