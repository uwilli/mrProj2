cmake_minimum_required(VERSION 3.10.2)
project(temperature_dev)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Libraries
add_subdirectory("${PROJECT_SOURCE_DIR}/../lib/pigpio" ${PROJECT_SOURCE_DIR}/build")

# Executable
add_executable(${PROJECT_NAME}
                ${PROJECT_SOURCE_DIR}/source/src/temp_TestingMain.cpp
                ${PROJECT_SOURCE_DIR}/source/src/mcp9808.cpp
                ${PROJECT_SOURCE_DIR}/source/src/pigpioI2c.cpp
                ${PROJECT_SOURCE_DIR}/source/src/raspiPigpio.cpp
                )
							
# threads needed for pigpio to compile correctly
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC pigpio
                                        PRIVATE Threads::Threads
                                        )

target_include_directories(${PROJECT_NAME} PUBLIC
                                "${PROJECT_BINARY_DIR}"
                                "${PROJECT_SOURCE_DIR}/../lib/pigpio"
                                "${PROJECT_SOURCE_DIR}/source/inc" )
