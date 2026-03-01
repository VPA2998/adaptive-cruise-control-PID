cmake_minimum_required(VERSION 3.10)
project(ACC_Simulator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
    src/vehicle.cpp
    src/pid_controller.cpp
)

add_executable(acc_simulator ${SOURCES})

# Tests - uncomment when test files are ready
# add_subdirectory(tests EXCLUDE_FROM_ALL)
