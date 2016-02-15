#!/bin/bash
PLOTOUTPUT=$1
DATADIR='data'

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Running time/log^2(n)"
set format y "%.0s*10^%T"
set yrange  [0.00000002:0.00000025]
set output "$PLOTOUTPUT/BFS_running_time.eps"

plot "$DATADIR/bfs_O3_vector_recursive.data" using (log(\$1)):(\$2) title "BFS g++ with -O3"

#plot "$DATADIR/bfs_O3_vector_recursive.data" using (log(\$1)):(\$2/(log(\$1)*log(\$1))) title "BFS -O3 #Recursive", \
#     "$DATADIR/bfs_O3_vector_iterative.data" using (log(\$1)):(\$2/(log(\$1)*log(\$1))) title "BFS -O3 Iterative"

GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Mispridictions/log(n)"
set yrange [0:1.5]
set output "$PLOTOUTPUT/BFS_branch_mispridictions.eps"

plot "$DATADIR/bfs_O3_vector_recursive.data" using (log(\$1)):(\$3/log(\$1)) title "BFS g++ with -O3"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Misses"

#set yrange [0:20]
set output "$PLOTOUTPUT/BFS_cache_misses.eps"

plot "$DATADIR/bfs_O3_vector_recursive.data" using (log(\$1)):4 title "L1 Cache misses", \
     "$DATADIR/bfs_O3_vector_recursive.data" using (log(\$1)):5 title "L2 Cache misses"
GPLOT
