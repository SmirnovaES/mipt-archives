cmake_minimum_required(VERSION 3.6)
project(Floyd)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES main.cpp tests/FloydTest.cpp src/Graph.cpp tests/Graph.h tests/InputTest.cpp)
add_executable(Floyd ${SOURCE_FILES} tests/FloydTest.cpp tests/InputTest.cpp)

target_link_libraries(Floyd gtest gtest_main)