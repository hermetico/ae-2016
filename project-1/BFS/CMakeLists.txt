cmake_minimum_required(VERSION 3.3)
project(BFS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp BFS.h)
add_executable(BFS ${SOURCE_FILES})
target_link_libraries(BFS papi)