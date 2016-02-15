cmake_minimum_required(VERSION 3.3)
project(DFS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES main.cpp DFSArray.cpp DFSArray.h)
add_executable(DFS ${SOURCE_FILES})