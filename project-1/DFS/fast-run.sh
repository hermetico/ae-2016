#!/bin/bash
input=$1
g++ -O3 main.cpp DFSArray.cpp DFSArray.h -std=c++11 -L/usr/local/lib -lpapi -o dfs
./dfs $1 $2 $3

