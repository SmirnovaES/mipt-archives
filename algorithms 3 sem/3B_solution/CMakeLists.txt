cmake_minimum_required(VERSION 3.6)
project(Transformations)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES main.cpp src/Transformations.cpp tests/Transformations.h tests/FunctionsTest.cpp tests/RecoveringTest.cpp)
add_executable(Transformations ${SOURCE_FILES} src/Transformations.cpp tests/Transformations.h tests/FunctionsTest.cpp tests/RecoveringTest.cpp)

target_link_libraries(Transformations gtest gtest_main)