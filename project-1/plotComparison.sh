#!/bin/bash
PLOTOUTPUT=$1
INORDERDATAFILE='InOrder/data/inOrder_O3_alpha_025.data'
BFSDATAFILE='BFS/data/bfs_O3_vector_test1.data'
DFSDATADIRFILE='DFS/data/dfs_array_recursive_continuous.data'

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Running time"
set format y "%.0s*10^%T"
set yrange  [0.00000002:0.00000080]
set output "$PLOTOUTPUT/binary_search_comparison_running_time.eps"

plot "$INORDERDATAFILE" using (log(\$1)/log(2)):2 title "InOrder -O3", \
     "$BFSDATAFILE" using (log(\$1)/log(2)):2 title "BFS -O3", \
     "$DFSDATADIRFILE" using (log(\$1)/log(2)):2 title "DFS -O3"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Branche Mispridictions/log(n)"
set yrange [0:1.5]
set output "$PLOTOUTPUT/binary_search_comparison_branch_mispredictions.eps"

plot "$INORDERDATAFILE" using (log(\$1)/log(2)):(\$3/(log(\$1)/log(2))) title "InOrder -O3", \
     "$BFSDATAFILE" using (log(\$1)/log(2)):(\$3/(log(\$1)/log(2))) title "BFS -O3", \
     "$DFSDATADIRFILE" using (log(\$1)/log(2)):(\$3/(log(\$1)/log(2))) title "DFS -O3"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Cache Misses"
set yrange [0:45]
set output "$PLOTOUTPUT/binary_search_comparison_cache_misses.eps"

plot "$INORDERDATAFILE" using (log(\$1)/log(2)):4 title "InOrder -O3: L1 Cache", \
     "$INORDERDATAFILE" using (log(\$1)/log(2)):5 title "InOrder -O3: L2 Cache", \
     "$BFSDATAFILE" using (log(\$1)/log(2)):4 title "BFS -O3: L1 Cache", \
     "$BFSDATAFILE" using (log(\$1)/log(2)):5 title "BFS -O3: L2 Cache", \
     "$DFSDATADIRFILE" using (log(\$1)/log(2)):4 title "DFS -O3: L1 Cache", \
     "$DFSDATADIRFILE" using (log(\$1)/log(2)):5 title "DFS -O3: L2 Cache"     
GPLOT