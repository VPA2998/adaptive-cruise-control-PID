cmake_minimum_required(VERSION 3.10)
project(ACC_Simulator CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/simulator.cpp
    src/pid_controller.cpp
)

# Create executable
add_executable(acc_simulator ${SOURCES})

# Optional: Add tests
enable_testing()
add_subdirectory(tests EXCLUDE_FROM_ALL)
