cmake_minimum_required(VERSION 3.6)
project(SuffArray)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES main.cpp src/SuffixArray.cpp tests/SuffixArray.h tests/AssignmentTest.cpp tests/AlgorithmTest.cpp)
add_executable(SuffArray ${SOURCE_FILES} src/SuffixArray.cpp tests/SuffixArray.h tests/AssignmentTest.cpp tests/AlgorithmTest.cpp)

target_link_libraries(SuffArray gtest gtest_main)