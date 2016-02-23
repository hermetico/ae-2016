#!/bin/bash
DATADIR='data'
BUILDFILE='inOrder'
mkdir -p $DATADIR

g++ -O3 main.cpp -L/usr/local/lib -lpapi -o $BUILDFILE
./$BUILDFILE 1 0.25 > $DATADIR/inOrder_O3_alpha_025.data
./$BUILDFILE 1 0.50 > $DATADIR/inOrder_O3_alpha_050.data
./$BUILDFILE 2 > $DATADIR/inOrder_O3_different_alpha.data

g++ main.cpp -L/usr/local/lib -lpapi -o $BUILDFILE
./$BUILDFILE 1 0.25 > $DATADIR/inOrder_alpha_025.data
rm $BUILDFILE
