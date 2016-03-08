#!/bin/bash
PLOTOUTPUT=$1
DATADIR='data'
INORDERDIR='../InOrder/data'

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Running time"
set format y "%.0s*10^%T"
set yrange  [0.00000000:0.00000080]
set output "$PLOTOUTPUT/BFS_running_time.eps"

plot "$DATADIR/bfs_O3_vector_test1.data" using (log(\$1)/log(2)):2 title "BFS"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Branche Mispridictions/log(n)"
set yrange [0:1]
set output "$PLOTOUTPUT/BFS_branch_mispredictions.eps"

plot "$DATADIR/bfs_O3_vector_test1.data" using (log(\$1)/log(2)):(\$3/(log(\$1)/log(2))) title "BFS"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Cache Misses"
set yrange [0:50]
set output "$PLOTOUTPUT/BFS_cache_misses.eps"

plot "$DATADIR/bfs_O3_vector_test1.data" using (log(\$1)/log(2)):4 title "BFS: L1 Cache", \
     "$DATADIR/bfs_O3_vector_test1.data" using (log(\$1)/log(2)):5 title "BFS: L2 Cache", \
     "$INORDERDIR/inOrder_O3_alpha_025.data" using (log(\$1)/log(2)):4 title "Inorder: L1 Cache", \
     "$INORDERDIR/inOrder_O3_alpha_025.data" using (log(\$1)/log(2)):5 title "Inorder: L2 Cache"
GPLOT



gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Cache Misses"
set yrange [0:50]
set output "$PLOTOUTPUT/BFS_cache_misses_with_fitings.eps"

plot "$DATADIR/bfs_O3_vector_test1.data" using (log(\$1)/log(2)):4 title "L1 Cache", \
     "$DATADIR/bfs_O3_vector_test1.data" using  (log(\$1)/log(2)):(2.5*log(\$1)/log(2)-34.5) title "2.5*log(n)" with linespoints, \
     "$DATADIR/bfs_O3_vector_test1.data" using (log(\$1)/log(2)):5 title "L2 Cache", \
     "$DATADIR/bfs_O3_vector_test1.data" using  (log(\$1)/log(2)):(2.5*log(\$1)/log(2)-38.5) title "2.5*log(n)" with linespoints, \

GPLOT
