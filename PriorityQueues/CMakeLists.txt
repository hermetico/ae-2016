cmake_minimum_required(VERSION 3.3)
project(PriorityQueues)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Simple/SimplePriorityQueue.h)
add_executable(PriorityQueues ${SOURCE_FILES})