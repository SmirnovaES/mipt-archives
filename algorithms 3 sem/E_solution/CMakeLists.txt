cmake_minimum_required(VERSION 3.6)
project(MaxFlow)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)


set(SOURCE_FILES main.cpp src/Flow.cpp tests/Flow.h tests/AssignmentTest.cpp tests/AlgorithmTest.cpp)
add_executable(MaxFlow ${SOURCE_FILES} tests/AssignmentTest.cpp tests/AlgorithmTest.cpp)

target_link_libraries(MaxFlow gtest gtest_main)