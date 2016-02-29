#!/bin/bash
DATADIR=$1
PLOTOUTPUT=$2


mkdir -p $PLOTOUTPUT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Running time"
set format y "%.0s*10^%T"
#set yrange  [0.00000000:0.00000080]
set output "$PLOTOUTPUT/priority_queue_running_time.eps"

plot "$DATADIR/simple_heap_test.data" using (log(\$1)/log(2)):(\$2)/(log(\$1)/log(2)) title "C++ Simple heap ",\
     "$DATADIR/sanders_simple_heap_test.data" using (log(\$1)/log(2)):(\$2)/(log(\$1)/log(2)) title "Bottom up Binary heap ",\
     "$DATADIR/sanders_heap4_test.data" using (log(\$1)/log(2)):(\$2)/(log(\$1)/log(2)) title "Bottom up aligned 4-ary heap",\
     "$DATADIR/sanders_knheap_test.data" using (log(\$1)/log(2)):(\$2)/(log(\$1)/log(2)) title "Kn heap"
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Branch Mispridictions"
set yrange [0:25]
set output "$PLOTOUTPUT/priority_queue_branch_mispridictions.eps"

plot "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):3 title "C++ simple heap", \
     "$DATADIR/sanders_simple_heap_test.data" using (log(\$1)/log(2)):3 title  "Bottom up Binary heap", \
     "$DATADIR/sanders_heap4_test.data" using  (log(\$1)/log(2)):3 title  "Bottom up aligned 4-ary heap",\
     "$DATADIR/sanders_knheap_test.data" using  (log(\$1)/log(2)):3 title  "Kn heap"
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Level 1 Cache Misses"
#set yrange [0:50]
set output "$PLOTOUTPUT/priority_queue_cache_misses_level_1.eps"

plot "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):4 title "C++ simple heap", \
     "$DATADIR/sanders_simple_heap_test.data" using  (log(\$1)/log(2)):4 title "Bottom up Binary heap", \
     "$DATADIR/sanders_heap4_test.data" using (log(\$1)/log(2)):4 title "Bottom up aligned 4-ary heap",\
     "$DATADIR/sanders_knheap_test.data" using (log(\$1)/log(2)):4 title "Kn heap"
GPLOT



gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "L2 Cache Misses"
#set yrange [0:50]
set output "$PLOTOUTPUT/priority_queue_cache_misses_level_2.eps"

plot "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):5 title "C++ simple heap", \
     "$DATADIR/sanders_simple_heap_test.data" using  (log(\$1)/log(2)):5 title "Bottom up Binary heap", \
     "$DATADIR/sanders_heap4_test.data" using (log(\$1)/log(2)):5 title "Bottom up aligned 4-ary heap", \
     "$DATADIR/sanders_knheap_test.data" using (log(\$1)/log(2)):5 title "Kn heap"
GPLOT

