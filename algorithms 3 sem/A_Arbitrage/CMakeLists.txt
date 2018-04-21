cmake_minimum_required(VERSION 3.6)
project(Arbitrage)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES main.cpp src/Arbitrage.cpp tests/Arbitrage.h tests/AlgorithmTest.cpp tests/AssignmentTest.cpp)
add_executable(Arbitrage ${SOURCE_FILES} src/Arbitrage.cpp tests/Arbitrage.h tests/AssignmentTest.cpp)

target_link_libraries(Arbitrage gtest gtest_main)