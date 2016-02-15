#!/bin/bash
PLOTOUTPUT='plots'
TEMPDIR='temp'
mkdir $TEMPDIR
mkdir $PLOTOUTPUT

g++ -O3 main.cpp DFSArray.cpp DFSArray.h -std=c++11 -L/usr/local/lib -lpapi -o dfs
./dfs > $TEMPDIR/dfs_array_recursive.data

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Running time/log^2(n)"
set format y "%.0s*10^%T"
set yrange [0:0.000000015]
set output "$PLOTOUTPUT/DFS_running_time.eps"

plot "$TEMPDIR/dfs_array_recursive.data" using (log(\$1)):(\$2/(log(\$1)*log(\$1))) title "DFS g++ with -O3"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Mispridictions"
#set yrange [0:5]
set output "$PLOTOUTPUT/DFS_branch_mispridictions.eps"

plot "$TEMPDIR/dfs_array_recursive.data" using (log(\$1)):(\$3) title "Branch mispredictions"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Misses"

#set yrange [0:20]
set output "$PLOTOUTPUT/DFS_cache_misses.eps"

plot "$TEMPDIR/dfs_array_recursive.data" using (log(\$1)):4 title "L1 Cache misses"
GPLOT



rm -r $TEMPDIR
