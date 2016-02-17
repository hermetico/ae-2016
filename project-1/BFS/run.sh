#!/bin/bash
DATADIR='data'
BUILDFILE='bfs'
mkdir -p $DATADIR

g++ -O3 main.cpp -L/usr/local/lib -lpapi -o $BUILDFILE
./bfs 1 > $DATADIR/bfs_O3_vector_test1.data
#./bfs 2 > $DATADIR/bfs_O3_vector_test2.data
#./bfs 3 > $DATADIR/bfs_O3_vector_test3.data

rm $BUILDFILE
