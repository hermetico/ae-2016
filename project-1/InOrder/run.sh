#!/bin/bash
DATADIR='data'
BUILDFILE='inOrder'
mkdir -p $DATADIR

g++ -O3 main.cpp -L/usr/local/lib -lpapi -o $BUILDFILE
./$BUILDFILE 1 0.25 > $DATADIR/inOrder_O3_constant_alpha.data
./$BUILDFILE 2 > $DATADIR/inOrder_O3_different_alpha.data

rm $BUILDFILE
