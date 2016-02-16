#!/bin/bash
DATADIR=$1
mkdir $DATADIR

g++ -O3 main.cpp DFSArray.cpp DFSArray.h -std=c++11 -L/usr/local/lib -lpapi -o dfs
./dfs 0 > $DATADIR/dfs_array_recursive_continuous.data
./dfs 2 >  $DATADIR/dfs_array_recursive_non_continuous.data

