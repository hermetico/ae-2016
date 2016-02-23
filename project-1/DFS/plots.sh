#!/bin/bash
PLOTOUTPUT=$1
DATADIR=$1

mkdir $PLOTOUTPUT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Running time"
set format y "%.0s*10^%T"
set yrange  [0.00000000:0.00000080]
set output "$PLOTOUTPUT/DFS_running_time.eps"

plot "$DATADIR/dfs_array_recursive_continuous.data" using (log(\$1)/log(2)):(\$2) title "DFS, alpha = 0.75"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Branche Mispridictions/log(n)"
set yrange [0:1]
set output "$PLOTOUTPUT/DFS_branch_mispridictions.eps"

plot "$DATADIR/dfs_array_recursive_continuous.data" using (log(\$1)/log(2)):(\$3/(log(\$1)/log(2))) title "DFS, alpha = 0.75"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Cache Misses"
set yrange [0:50]
set output "$PLOTOUTPUT/DFS_cache_misses.eps"

plot "$DATADIR/dfs_array_recursive_continuous.data" using (log(\$1)/log(2)):4 title "L1 Cache", \
     "$DATADIR/dfs_array_recursive_continuous.data" using (log(\$1)/log(2)):5 title "L2 Cache"
GPLOT

