#cmake_minimum_required(VERSION 3.3)
project(PriorityQueues)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -g -std=c++11")

set(SOURCE_FILES
        main.cpp
        Sanders/heap-CLR.h
        Sanders/heap4.h
        Sanders/knheap.h
        Sanders/shared/util.h
        Simple/VectorHeap.h
        )

add_executable(PriorityQueues ${SOURCE_FILES})
target_link_libraries(PriorityQueues papi)