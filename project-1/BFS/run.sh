#!/bin/bash
DATADIR='data'
mkdir $DATADIR

g++ -O3 main.cpp -L/usr/local/lib -lpapi -o bfs
make
./bfs i > $DATADIR/bfs_O3_vector_iterative.data
./bfs > $DATADIR/bfs_O3_vector_recursive.data
