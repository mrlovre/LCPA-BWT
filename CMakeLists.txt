cmake_minimum_required(VERSION 3.3)
project(LCPA-BWT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/algorithms.cpp src/algorithms.h)
add_executable(testMain ${SOURCE_FILES})