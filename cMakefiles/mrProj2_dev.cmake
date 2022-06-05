cmake_minimum_required(VERSION 3.10)
project(mrProj2
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Run via DAEMON for ability of running multiple programs simultaneously
add_compile_definitions(DAEMON)

# Temperature sensor development
add_executable(temp_dev
                ${PROJECT_SOURCE_DIR}/src/temp_TestingMain.cpp
                ${PROJECT_SOURCE_DIR}/src/mcp9808.cpp
                ${PROJECT_SOURCE_DIR}/src/pigpioI2c.cpp
                ${PROJECT_SOURCE_DIR}/src/raspiPigpio.cpp
)

target_link_libraries(temp_dev
                        pigpio
                        ${pigpiod_if2_LIBRARY}
)

target_include_directories(temp_dev
                           PUBLIC ${PROJECT_SOURCE_DIR}/inc
)

# Gyro & accelerometer sensor development
add_executable(gyro_dev
                ${PROJECT_SOURCE_DIR}/src/gyro_TestingMain.cpp
                ${PROJECT_SOURCE_DIR}/src/lsm6ds33.cpp
                ${PROJECT_SOURCE_DIR}/src/vecXYZ.cpp
                ${PROJECT_SOURCE_DIR}/src/pigpioI2c.cpp
                ${PROJECT_SOURCE_DIR}/src/raspiPigpio.cpp
)

target_link_libraries(gyro_dev
                        pigpio
                        ${pigpiod_if2_LIBRARY}
)

target_include_directories(gyro_dev
                           PUBLIC ${PROJECT_SOURCE_DIR}/inc
)

# IO-Expander development
add_executable(ioExp_dev
                ${PROJECT_SOURCE_DIR}/src/ioExp_TestingMain.cpp
                ${PROJECT_SOURCE_DIR}/src/pca9554b.cpp
                ${PROJECT_SOURCE_DIR}/src/pigpioI2c.cpp
                ${PROJECT_SOURCE_DIR}/src/raspiPigpio.cpp
)

target_link_libraries(ioExp_dev
                        pigpio
                        ${pigpiod_if2_LIBRARY}
)

target_include_directories(ioExp_dev
                           PUBLIC ${PROJECT_SOURCE_DIR}/inc
)

# motor development
add_executable(motor_dev
                ${PROJECT_SOURCE_DIR}/src/motor_TestingMain.cpp
                ${PROJECT_SOURCE_DIR}/src/tb6612fng.cpp
                ${PROJECT_SOURCE_DIR}/src/pigpioPwm.cpp
                ${PROJECT_SOURCE_DIR}/src/raspiPigpio.cpp
)

target_link_libraries(motor_dev
                        pigpio
                        ${pigpiod_if2_LIBRARY}
)

target_include_directories(motor_dev
                           PUBLIC ${PROJECT_SOURCE_DIR}/inc
)

# servo development
add_executable(servo_dev
                ${PROJECT_SOURCE_DIR}/src/servo_TestingMain.cpp
                ${PROJECT_SOURCE_DIR}/src/servo.cpp
                ${PROJECT_SOURCE_DIR}/src/pca9554b.cpp
                ${PROJECT_SOURCE_DIR}/src/pigpioPwm.cpp
                ${PROJECT_SOURCE_DIR}/src/pigpioI2c.cpp
                ${PROJECT_SOURCE_DIR}/src/raspiPigpio.cpp
)

target_link_libraries(servo_dev
                        pigpio
                        ${pigpiod_if2_LIBRARY}
)

target_include_directories(servo_dev
                           PUBLIC ${PROJECT_SOURCE_DIR}/inc
)
