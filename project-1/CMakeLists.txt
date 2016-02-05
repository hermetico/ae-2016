cmake_minimum_required(VERSION 3.3)
project(assignment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES tests/binary-search.cpp tests/test-alpha.cpp)
add_executable(assignment ${SOURCE_FILES})
