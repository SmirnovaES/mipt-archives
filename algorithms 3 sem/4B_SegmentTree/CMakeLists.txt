cmake_minimum_required(VERSION 3.6)
project(SegmentTree)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES main.cpp src/SegmentTree.cpp tests/SegmentTree.h tests/AlgorithmTest.cpp tests/AssignmentTest.cpp)
add_executable(SegmentTree ${SOURCE_FILES} src/SegmentTree.cpp tests/SegmentTree.h tests/AlgorithmTest.cpp tests/AssignmentTest.cpp)

target_link_libraries(SegmentTree gtest gtest_main)