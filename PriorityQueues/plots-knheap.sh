#!/bin/bash
DATADIR=$1
PLOTOUTPUT=$2


mkdir -p $PLOTOUTPUT

############ Comparisons #################

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "(T(deleteMin) + T(insert))"
set format y "%.0s*10^%T"
#set yrange  [0.00000000:0.00000080]
set output "$PLOTOUTPUT/kn_heap_running_time.eps"

plot "$DATADIR/simple_heap_test.data" using (log(\$1)/log(2)):2 title "Binary heap",\
     "$DATADIR/sanders_knheap_test.data" using (log(\$1)/log(2)):2 title "Kn heap"

GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Branch Mispridictions/log(n)"
set yrange [0:0.8]
set output "$PLOTOUTPUT/kn_heap_branch_mispridictions.eps"

plot "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):(\$3)/(log(\$1)/log(2)) title "Binary heap", \
     "$DATADIR/sanders_knheap_test.data" using  (log(\$1)/log(2)):(\$3)/(log(\$1)/log(2)) title  "Kn heap"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Level 1 Cache Misses"
#set yrange [0:50]
set output "$PLOTOUTPUT/kn_heap_cache_misses_level_1.eps"

plot "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):4 title "Binary heap", \
     "$DATADIR/sanders_knheap_test.data" using (log(\$1)/log(2)):4 title "Kn heap"

GPLOT



gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "L2 Cache Misses"
#set yrange [0:50]
set output "$PLOTOUTPUT/kn_heap_cache_misses_level_2.eps"

plot "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):5 title "Binary heap", \
     "$DATADIR/sanders_knheap_test.data" using (log(\$1)/log(2)):5 title "Kn heap"
GPLOT



############ KN Heap #################

