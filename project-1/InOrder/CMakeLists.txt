cmake_minimum_required(VERSION 3.3)
project(InOrder)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp InOrder.h ../Shared/Measure.h ../Shared/Utils.h)
add_executable(InOrder ${SOURCE_FILES})
target_link_libraries(InOrder papi)
