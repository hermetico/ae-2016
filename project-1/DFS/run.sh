#!/bin/bash
PLOTOUTPUT=$1
TEMPDIR='temp'
mkdir $TEMPDIR

g++ -O3 main.cpp DFSArray.cpp DFSArray.h -std=c++11 -L/usr/local/lib -lpapi -o dfs
./dfs > $TEMPDIR/dfs_array_recursive.data
