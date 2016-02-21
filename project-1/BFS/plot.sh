#!/bin/bash
PLOTOUTPUT=$1
DATADIR='data'

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Running time"
set format y "%.0s*10^%T"
#set yrange  [0.00000002:0.00000025]
set output "$PLOTOUTPUT/BFS_running_time.eps"

plot "$DATADIR/bfs_O3_vector_test1.data" using (log(\$1)/log(2)):2 title "BFS -O3"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Branche Mispridictions/log(n)"
set yrange [0:1.5]
set output "$PLOTOUTPUT/BFS_branch_mispredictions.eps"

plot "$DATADIR/bfs_O3_vector_test1.data" using (log(\$1)/log(2)):(\$3/(log(\$1)/log(2))) title "BFS -O3"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Cache Misses"
set yrange [0:30]
set output "$PLOTOUTPUT/BFS_cache_misses.eps"

plot "$DATADIR/bfs_O3_vector_test1.data" using (log(\$1)/log(2)):4 title "BFS -O3: L1 Cache", \
     "$DATADIR/bfs_O3_vector_test1.data" using (log(\$1)/log(2)):5 title "BFS -O3: L2 Cache"
GPLOT
