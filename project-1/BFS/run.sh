#!/bin/bash
DATADIR='data'
BUILDFILE='bfs'
mkdir -p $DATADIR

g++ -O3 main.cpp -L/usr/local/lib -lpapi -o $BUILDFILE
make
./bfs i > $DATADIR/bfs_O3_vector_iterative.data
./bfs > $DATADIR/bfs_O3_vector_recursive.data
./bfs r 2 > $DATADIR/bfs_O3_vector_recursive_randMulitplier_2.data

rm $BUILDFILE
