cmake_minimum_required(VERSION 3.3)
project(DFS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -o dfs")

set(SOURCE_FILES main.cpp DFSArray.cpp DFSArray.h ../Shared/Measure.h ../Shared/Utils.h)
add_executable(DFS ${SOURCE_FILES})
target_link_libraries(DFS papi)