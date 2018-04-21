cmake_minimum_required(VERSION 3.6)
project(D_MST)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES main.cpp src/MST.cpp tests/MST.h tests/AssignmentTest.cpp tests/AlgorithmTest.cpp)
add_executable(D_MST ${SOURCE_FILES} src/MST.cpp tests/MST.h tests/AssignmentTest.cpp tests/AlgorithmTest.cpp)

target_link_libraries(D_MST gtest gtest_main)