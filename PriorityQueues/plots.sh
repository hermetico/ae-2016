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
set output "$PLOTOUTPUT/priority_queue_running_time.eps"

plot "$DATADIR/simple_heap_test.data" using (log(\$1)/log(2)):2 title "Binary heap",\
     "$DATADIR/sanders_heap4_test.data" using (log(\$1)/log(2)):2 title "Bottom up aligned 4-ary heap",\
     "$DATADIR/sanders_knheap_test.data" using (log(\$1)/log(2)):2 title "Kn heap"

     #"$DATADIR/sanders_simple_heap_test.data" using (log(\$1)/log(2)):2 title "Bottom up Binary heap ",\

GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Branch Mispridictions/log(n)"
set yrange [0:0.8]
set output "$PLOTOUTPUT/priority_queue_branch_mispridictions.eps"

plot "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):(\$3)/(log(\$1)/log(2)) title "Binary heap", \
     "$DATADIR/sanders_heap4_test.data" using  (log(\$1)/log(2)):(\$3)/(log(\$1)/log(2)) title  "Bottom up aligned 4-ary heap",\
     "$DATADIR/sanders_knheap_test.data" using  (log(\$1)/log(2)):(\$3)/(log(\$1)/log(2)) title  "Kn heap"

     #"$DATADIR/sanders_simple_heap_test.data" using (log(\$1)/log(2)):(\$3)/(log(\$1)/log(2)) title  "Bottom up Binary heap", \

GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Level 1 Cache Misses"
#set yrange [0:50]
set output "$PLOTOUTPUT/priority_queue_cache_misses_level_1.eps"

plot "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):4 title "Binary heap", \
     "$DATADIR/sanders_heap4_test.data" using (log(\$1)/log(2)):4 title "Bottom up aligned 4-ary heap",\
     "$DATADIR/sanders_knheap_test.data" using (log(\$1)/log(2)):4 title "Kn heap"
     #"$DATADIR/sanders_simple_heap_test.data" using  (log(\$1)/log(2)):4 title "Bottom up Binary heap", \

GPLOT



gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "L2 Cache Misses"
#set yrange [0:50]
set output "$PLOTOUTPUT/priority_queue_cache_misses_level_2.eps"

plot "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):5 title "Binary heap", \
     "$DATADIR/sanders_heap4_test.data" using (log(\$1)/log(2)):5 title "Bottom up aligned 4-ary heap", \
     "$DATADIR/sanders_knheap_test.data" using (log(\$1)/log(2)):5 title "Kn heap"

     #"$DATADIR/sanders_simple_heap_test.data" using  (log(\$1)/log(2)):5 title "Bottom up Binary heap", \

GPLOT


############ Binary Heap #################


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Level 1 Cache Misses"
set yrange [0:20]
#set xrange [14:24]
set output "$PLOTOUTPUT/priority_queue_BinaryHeap_cache_misses.eps"

plot "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):(\$4) title "Cache Level 1", \
     "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):(0.75*log(\$1)/log(2)-9.5) title "0.75*log(n)", \
     "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):(\$5) title "Cache Level 2", \
     "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):(0.75*log(\$1)/log(2)-11.7) title "1.35*log(n)"
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Branch Mispridictions"
set yrange [0:5]
set output "$PLOTOUTPUT/priority_queue_BinaryHeap_branch_mispridictions.eps"

plot "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):3 title "Binary heap", \

     #"$DATADIR/sanders_simple_heap_test.data" using (log(\$1)/log(2)):(\$3)/(log(\$1)/log(2)) title  "Bottom up Binary heap", \

GPLOT