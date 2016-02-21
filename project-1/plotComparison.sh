#!/bin/bash
PLOTOUTPUT=$1
INORDERDATAFILE='InOrder/data/inOrder_O3_constant_alpha.data'
BFSDATAFILE='BFS/data/bfs_O3_vector_test1.data'
DFSDATADIR='DFS/plots-alpha-test-1000000-length-no-random-number'

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Running time"
set format y "%.0s*10^%T"
set yrange  [0.00000002:0.00000080]
set output "$PLOTOUTPUT/comparison_running_time.eps"

plot "$INORDERDATAFILE" using (log(\$1)/log(2)):2 title "InOrder -O3", \
     "$BFSDATAFILE" using (log(\$1)/log(2)):2 title "BFS -O3"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Branche Mispridictions/log(n)"
set yrange [0:1.5]
set output "$PLOTOUTPUT/comparison_branch_mispredictions.eps"

plot "$INORDERDATAFILE" using (log(\$1)/log(2)):(\$3/(log(\$1)/log(2))) title "InOrder -O3", \
     "$BFSDATAFILE" using (log(\$1)/log(2)):(\$3/(log(\$1)/log(2))) title "BFS -O3"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Cache Misses"
set yrange [0:45]
set output "$PLOTOUTPUT/comparison_cache_misses.eps"

plot "$INORDERDATAFILE" using (log(\$1)/log(2)):4 title "InOrder -O3: L1 Cache", \
     "$INORDERDATAFILE" using (log(\$1)/log(2)):5 title "InOrder -O3: L2 Cache", \
     "$BFSDATAFILE" using (log(\$1)/log(2)):4 title "BFS -O3: L1 Cache", \
     "$BFSDATAFILE" using (log(\$1)/log(2)):5 title "BFS -O3: L2 Cache"
GPLOT
