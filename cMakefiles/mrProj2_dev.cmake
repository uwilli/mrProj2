cmake_minimum_required(VERSION 3.10)
project(mrProj2
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Temperature sensor development
add_executable(temp_dev
                ${PROJECT_SOURCE_DIR}/src/temp_TestingMain.cpp
                ${PROJECT_SOURCE_DIR}/src/mcp9808.cpp
                ${PROJECT_SOURCE_DIR}/src/pigpioI2c.cpp
                ${PROJECT_SOURCE_DIR}/src/raspiPigpio.cpp
)

target_link_libraries(temp_dev
                        pigpio
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
)

target_include_directories(gyro_dev
                           PUBLIC ${PROJECT_SOURCE_DIR}/inc
)
