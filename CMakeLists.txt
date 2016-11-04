cmake_minimum_required(VERSION 3.3)
project(LCPA-BWT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES src/algorithms.cpp src/algorithms.h src/Bwt.h src/Bwt.cpp src/Alphabet.h src/Alphabet.cpp src/main.cpp)
add_executable(testMain ${SOURCE_FILES})