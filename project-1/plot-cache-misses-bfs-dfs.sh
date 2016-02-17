#!/bin/bash
PLOTOUTPUT=$2
DATADIR=$1

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Misses"
set yrange [0:30]
set output "BFS-DFS-cache_misses.eps"

plot "DFS/test-random-inputs-av-100000/dfs_array_recursive_continuous.data" using (log(\$1)/log(2)):4 title "DFS L1 Cache misses", \
     "DFS/test-random-inputs-av-100000/dfs_array_recursive_continuous.data" using (log(\$1)/log(2)):5 title "DFS L2 Cache misses", \
     "BFS/data/bfs_O3_vector_recursive.data" using (log(\$1)/log(2)):4 title "BFS L1 Cache misses", \
     "BFS/data/bfs_O3_vector_recursive.data" using (log(\$1)/log(2)):5 title "BFS L2 Cache misses"
GPLOT