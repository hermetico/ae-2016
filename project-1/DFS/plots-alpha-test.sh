#!/bin/bash
PLOTOUTPUT=$2
DATADIR=$1

mkdir $PLOTOUTPUT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Running time"
set format y "%.0s*10^%T"
#set yrange  [0.00000002:0.00000025]
set output "$PLOTOUTPUT/DFS_running_time.eps"

plot "$DATADIR/dfs_array_skewed_test.data" using (\$1):(\$2) title "Modifing alpha"
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Mispridictions/log(n)"
set output "$PLOTOUTPUT/DFS_branch_mispridictions.eps"

plot "$DATADIR/dfs_array_skewed_test.data" using 1:3 title "Modifing alpha"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Misses"
set yrange [0:30]
set output "$PLOTOUTPUT/DFS_cache_misses.eps"

plot "$DATADIR/dfs_array_skewed_test.data" using (\$1):4 title "Cache level 1", \
     "$DATADIR/dfs_array_skewed_test.data" using (\$1):5 title "Cache level 2", \
     6
GPLOT