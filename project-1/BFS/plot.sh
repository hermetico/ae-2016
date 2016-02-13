#!/bin/bash
PLOTOUTPUT=$1
TEMPDIR='temp'
mkdir $TEMPDIR

g++ -O3 main.cpp -L/usr/local/lib -lpapi -o bfs
./bfs i > $TEMPDIR/bfs_O3_vector_iterative.data
./bfs > $TEMPDIR/bfs_O3_vector_recursive.data

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Running time/log^2(n)"
set format y "%.0s*10^%T"
set yrange [0:0.000000015]
set output "$PLOTOUTPUT/BFS_running_time.eps"

plot "$TEMPDIR/bfs_O3_vector_recursive.data" using (log(\$1)):(\$2/(log(\$1)*log(\$1))) title "BFS g++ with -O3"

#plot "$TEMPDIR/bfs_O3_vector_recursive.data" using (log(\$1)):(\$2/(log(\$1)*log(\$1))) title "BFS -O3 #Recursive", \
#     "$TEMPDIR/bfs_O3_vector_iterative.data" using (log(\$1)):(\$2/(log(\$1)*log(\$1))) title "BFS -O3 Iterative"

GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Mispridictions/log^2(n)"
#set yrange [0:5]
set output "$PLOTOUTPUT/BFS_branch_mispridictions.eps"

plot "$TEMPDIR/bfs_O3_vector_recursive.data" using (log(\$1)):(\$3/(log(\$1)*log(\$1))) title "Branch mispredictions"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Misses"

#set yrange [0:20]
set output "$PLOTOUTPUT/BFS_cache_misses.eps"

plot "$TEMPDIR/bfs_O3_vector_recursive.data" using (log(\$1)):4 title "L1 Cache misses", \
     "$TEMPDIR/bfs_O3_vector_recursive.data" using (log(\$1)):5 title "L2 Cache misses"
GPLOT



rm -r $TEMPDIR
