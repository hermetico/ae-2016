#!/bin/bash
DATADIR=$1
mkdir $DATADIR

g++ -O3 main.cpp DFSArray.cpp DFSArray.h ../Shared/Measure.h ../Shared/Utils.h -std=c++11 -L/usr/local/lib -lpapi -o dfs
./dfs 2 >  $DATADIR/dfs_array_skewed_test.data

