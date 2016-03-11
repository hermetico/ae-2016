#cmake_minimum_required(VERSION 3.3)
project(MatrixMult)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -fopenmp")

set(SOURCE_FILES main.cpp methods/tiledmult.h methods/imatrixmult.h methods/recmult.h methods/simplemult.h methods/recmult_parallel.h)
add_executable(MatrixMult ${SOURCE_FILES})
target_link_libraries(MatrixMult papi)