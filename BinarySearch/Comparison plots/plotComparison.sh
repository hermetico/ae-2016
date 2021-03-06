#!/bin/bash
PLOTOUTPUT=$1
INORDERDATAFILE='InOrder/data/inOrder_O3_alpha_025.data'
BFSDATAFILE='BFS/data/bfs_O3_vector_test1.data'
DFSDATADIRFILE='DFS/data/dfs_array_recursive_continuous.data'

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Running time [seconds]"
set format y "%.1s*10^{%S}"
set yrange  [0.00000002:0.00000050]
set output "$PLOTOUTPUT/binary_search_comparison_running_time.eps"

plot "$INORDERDATAFILE" using (log(\$1)/log(2)):2 title "Inorder, alpha = 0.25", \
     "$BFSDATAFILE" using (log(\$1)/log(2)):2 title "BFS", \
     "$DFSDATADIRFILE" using (log(\$1)/log(2)):2 title "DFS, alpha = 0.75"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Branche Mispridictions/log(n)"
set yrange [0:1.0]
set output "$PLOTOUTPUT/binary_search_comparison_branch_mispredictions.eps"

plot "$INORDERDATAFILE" using (log(\$1)/log(2)):(\$3/(log(\$1)/log(2))) title "Inorder, alpha = 0.25", \
     "$BFSDATAFILE" using (log(\$1)/log(2)):(\$3/(log(\$1)/log(2))) title "BFS", \
     "$DFSDATADIRFILE" using (log(\$1)/log(2)):(\$3/(log(\$1)/log(2))) title "DFS, alpha = 0.75"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Cache Misses"
set yrange [0:35]
set output "$PLOTOUTPUT/binary_search_comparison_L1_cache_misses.eps"

plot "$INORDERDATAFILE" using (log(\$1)/log(2)):4 title "Inorder, alpha = 0.25: L1 Cache", \
     "$BFSDATAFILE" using (log(\$1)/log(2)):4 title "BFS: L1 Cache", \
     "$DFSDATADIRFILE" using (log(\$1)/log(2)):4 title "DFS, alpha = 0.75: L1 Cache"

GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Cache Misses"
set yrange [0:35]
set output "$PLOTOUTPUT/binary_search_comparison_L2_cache_misses.eps"

plot "$INORDERDATAFILE" using (log(\$1)/log(2)):5 title "Inorder, alpha = 0.25: L2 Cache", \
     "$BFSDATAFILE" using (log(\$1)/log(2)):5 title "BFS: L2 Cache", \
     "$DFSDATADIRFILE" using (log(\$1)/log(2)):5 title "DFS, alpha = 0.75: L2 Cache"     
GPLOT
