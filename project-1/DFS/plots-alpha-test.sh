#!/bin/bash
PLOTOUTPUT=$1
DATADIR=$1

mkdir $PLOTOUTPUT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "Alpha"
set ylabel "Running time [seconds]"
set format y "%.1s*10^{%S}"
#set yrange  [0.00000002:0.00000025]
set output "$PLOTOUTPUT/DFS_alpha_running_time.eps"

plot "$DATADIR/dfs_array_skewed_test.data" using (\$1):(\$2) title "N = 10^7"
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "Alpha"
set ylabel "Mispridictions"
set output "$PLOTOUTPUT/DFS_alpha_branch_mispridictions.eps"

plot "$DATADIR/dfs_array_skewed_test.data" using 1:3 title "N = 10^7"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "Alpha"
set ylabel "Cache Misses"
set yrange [0:30]
set output "$PLOTOUTPUT/DFS_alpha_cache_misses.eps"

plot "$DATADIR/dfs_array_skewed_test.data" using (\$1):4 title "L1 Cache", \
     "$DATADIR/dfs_array_skewed_test.data" using (\$1):5 title "L2 Cahce"
GPLOT

