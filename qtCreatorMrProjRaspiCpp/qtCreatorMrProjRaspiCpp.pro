TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../GpioTests/gyro_TestingMain.cpp \
    ../GpioTests/temp_DemoMcp9808.cpp \
    ../GpioTests/temp_TestingMain.cpp \
    ../cppClasses/lsm6ds33/lsm6ds33.cpp \
    ../cppClasses/mcp9808/mcp9808.cpp \
    ../cppClasses/pigpioI2c/pigpioI2c.cpp \
    ../cppClasses/raspiPigpio/raspiPigpio.cpp \
    ../cppClasses/vecXYZ/vecxyz.cpp

HEADERS += \
    ../cppClasses/lsm6ds33/lsm6ds33.h \
    ../cppClasses/mcp9808/mcp9808.h \
    ../cppClasses/pigpioI2c/pigpioI2c.h \
    ../cppClasses/raspiPigpio/raspiPigpio.h \
    ../cppClasses/vecXYZ/vecxyz.h

INCLUDEPATH += \
    ../cppClasses/vecXYZ \
    ../cppClasses/lsm6ds33 \
    ../cppClasses/mcp9808 \
    ../cppClasses/pigpioI2c \
    ../cppClasses/raspiPigpio
