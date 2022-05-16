cmake_minimum_required(VERSION 3.10)
project(mrProj2
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Executable
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
