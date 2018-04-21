cmake_minimum_required(VERSION 3.6)
project(PrefixFunction)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)


set(SOURCE_FILES main.cpp src/PrefixFunction.cpp tests/PrefixFunction.h tests/BuildingTest.cpp tests/AlgorithmTest.cpp)
add_executable(PrefixFunction ${SOURCE_FILES} src/PrefixFunction.cpp tests/PrefixFunction.h tests/BuildingTest.cpp tests/AlgorithmTest.cpp)

target_link_libraries(PrefixFunction gtest gtest_main)