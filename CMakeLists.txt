cmake_minimum_required(VERSION 3.6)
project(lab5_omp)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-march=bdver1 -mtune=bdver1 -fopenmp -O3")
set(CMAKE_C_FLAGS "-march=bdver1 -mtune=bdver1 -fopenmp -O3")


set(SOURCE_FILES main.cpp)
add_executable(lab5_omp ${SOURCE_FILES})