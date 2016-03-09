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

plot "$DATADIR/simple_heap_test.data" using (log(\$1)/log(2)):2 title "Binary Heap",\
     "$DATADIR/sanders_heap4_test.data" using (log(\$1)/log(2)):2 title "Bottom up aligned 4-ary Heap",\
     "$DATADIR/sanders_knheap_test.data" using (log(\$1)/log(2)):2 title "KN Heap"

GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Branch Mispridictions/log(n)"
set yrange [0:0.8]
set output "$PLOTOUTPUT/priority_queue_branch_mispridictions.eps"

plot "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):(\$3)/(log(\$1)/log(2)) title "Binary Heap", \
     "$DATADIR/sanders_heap4_test.data" using  (log(\$1)/log(2)):(\$3)/(log(\$1)/log(2)) title  "Bottom up aligned 4-ary Heap", \
     "$DATADIR/sanders_knheap_test.data" using  (log(\$1)/log(2)):(\$3)/(log(\$1)/log(2)) title  "KN Heap"

     #"$DATADIR/sanders_simple_heap_test.data" using (log(\$1)/log(2)):(\$3)/(log(\$1)/log(2)) title  "Bottom up Binary heap", \

GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Level 1 Cache Misses"
set yrange [0:12]
set output "$PLOTOUTPUT/priority_queue_cache_misses_level_1.eps"

plot "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):4 title "Binary Heap", \
     "$DATADIR/sanders_heap4_test.data" using (log(\$1)/log(2)):4 title "Bottom up aligned 4-ary Heap",\
     "$DATADIR/sanders_knheap_test.data" using (log(\$1)/log(2)):4 title "KN Heap"
     #"$DATADIR/sanders_simple_heap_test.data" using  (log(\$1)/log(2)):4 title "Bottom up Binary heap", \

GPLOT



gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "L2 Cache Misses"
set yrange [0:10]
set output "$PLOTOUTPUT/priority_queue_cache_misses_level_2.eps"

plot "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):5 title "Binary Heap", \
     "$DATADIR/sanders_heap4_test.data" using (log(\$1)/log(2)):5 title "Bottom up aligned 4-ary Heap", \
     "$DATADIR/sanders_knheap_test.data" using (log(\$1)/log(2)):5 title "KN Heap"

     #"$DATADIR/sanders_simple_heap_test.data" using  (log(\$1)/log(2)):5 title "Bottom up Binary heap", \

GPLOT


############ Binary Heap #################

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "(T(deleteMin) + T(insert))"
set format y "%.0s*10^%T"
set yrange  [0.00000000:0.00000035]
set output "$PLOTOUTPUT/priority_queue_running_time_simple_heap_with_fitting.eps"

plot "$DATADIR/simple_heap_test.data" using (log(\$1)/log(2)):2 title "Binary Heap",\
     "$DATADIR/simple_heap_test.data" using (log(\$1)/log(2)):(6.25*10**(-9)*log(\$1)/log(2)-0.5*10**(-9)) title "6.25*10^{-9}*log(n)" with linespoints, \
     "$DATADIR/simple_heap_test.data" using (log(\$1)/log(2)):(11.5*10**(-9)*log(\$1)/log(2)-80*10**(-9)) title "12.5*10^{-9}*log(n)" with linespoints, \
     "$DATADIR/simple_heap_test.data" using (log(\$1)/log(2)):(47*10**(-9)*log(\$1)/log(2)-805*10**(-9)) title "47*10^{-9}*log(n)" with linespoints


GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Level 1 Cache Misses"
set yrange [0:12]
#set xrange [14:24]
set output "$PLOTOUTPUT/priority_queue_BinaryHeap_cache_misses.eps"

plot "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):(\$4) title "Cache Level 1", \
     "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):(0.75*log(\$1)/log(2)-9.5) title "0.75*log(n)" with linespoints, \
     "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):(\$5) title "Cache Level 2", \
     "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):(0.75*log(\$1)/log(2)-11.7) title "0.75*log(n)" with linespoints, \
     "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):(0.75*log(\$1)/log(2)-11.7) title "0.75*log(n)" with linespoints

GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Branch Mispridictions"
set yrange [0:5]
set output "$PLOTOUTPUT/priority_queue_BinaryHeap_branch_mispridictions.eps"

plot "$DATADIR/simple_heap_test.data" using  (log(\$1)/log(2)):3 title "Binary Heap"

     #"$DATADIR/sanders_simple_heap_test.data" using (log(\$1)/log(2)):(\$3)/(log(\$1)/log(2)) title  "Bottom up Binary heap", \

GPLOT


############ 4-ary Heap #################

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "(T(deleteMin) + T(insert))"
set format y "%.0s*10^%T"
set yrange  [0.00000000:0.00000025]
set output "$PLOTOUTPUT/priority_queue_running_time_sanders_heap4_with_fitting.eps"

plot "$DATADIR/sanders_heap4_test.data" using (log(\$1)/log(2)):2 title "Bottom up aligned 4-ary Heap",\
     "$DATADIR/sanders_heap4_test.data" using (log(\$1)/log(2)):(4.0*10**(-9)*log(\$1)/log(2)+15*10**(-9)) title "4*10^{-9}*log(n)"  with linespoints, \
     "$DATADIR/sanders_heap4_test.data" using (log(\$1)/log(2)):(7.2*10**(-9)*log(\$1)/log(2)-3.5*10**(-8)) title "7.2*10^{-9}*log(n)" with linespoints, \
     "$DATADIR/sanders_heap4_test.data" using (log(\$1)/log(2)):(25*10**(-9)*log(\$1)/log(2)-40*10**(-8)) title "25*10^{-9}*log(n)" with linespoints


GPLOT



############ KN Heap #################

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "(T(deleteMin) + T(insert))"
set format y "%.0s*10^%T"
set yrange  [0.00000000:0.00000020]
set output "$PLOTOUTPUT/priority_queue_running_time_sanders_knheap_with_fitting.eps"

plot "$DATADIR/sanders_knheap_test.data" using (log(\$1)/log(2)):2 title "Kn Heap", \
     "$DATADIR/sanders_knheap_test.data" using (log(\$1)/log(2)):(2.5*10**(-9)*log(\$1)/log(2)+30*10**(-9)) title "2.5*10^{-9}*log(n)" with linespoints

GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "(T(deleteMin) + T(insert))"
set format y "%.0s*10^%T"
#set yrange  [0.00000000:0.00000080]
set output "$PLOTOUTPUT/kn_heap_running_time.eps"

plot "$DATADIR/sanders_knheap_test.data" using (log(\$1)/log(2)):2 title "KN Heap"
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Branch Mispridictions"
set yrange [0:20]
set output "$PLOTOUTPUT/kn_heap_branch_mispridictions.eps"

plot "$DATADIR/sanders_knheap_test.data" using  (log(\$1)/log(2)):3 title "Kn heap", \
     "$DATADIR/sanders_knheap_test.data" using  (log(\$1)/log(2)):((log(\$1)/log(2) * 1/4.25) + 2.5 ) title "1/4.25 * log(n)" with linespoints
     #(x/4.2) + 2.5

GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Level 1 Cache Misses"
set yrange [0:5]
#set xrange [14:24]
set output "$PLOTOUTPUT/kn_heap_cache_misses_l1.eps"

plot "$DATADIR/sanders_knheap_test.data" using  (log(\$1)/log(2)):4 title "KN Heap", \
     "$DATADIR/sanders_knheap_test.data" using  (log(\$1)/log(2)):(0.015 * (log(\$1)/log(2)) ) title "0.015 * log(n)" with linespoints
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Level 2 Cache Misses"
set yrange [-0.5:2]
#set xrange [14:24]
set output "$PLOTOUTPUT/kn_heap_cache_misses_l2.eps"

plot    "$DATADIR/sanders_knheap_test.data" using  (log(\$1)/log(2)):(\$5) title "KN Heap", \
        "$DATADIR/sanders_knheap_test.data" using  (log(\$1)/log(2)):((0.01 * log(\$1)/log(2)) -0.1 ) title "0.01 * log(n)" with linespoints
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel " Cache Misses"
#set yrange [0:20]
#set xrange [14:24]
set output "$PLOTOUTPUT/kn_heap_cache_misses_l1-2.eps"

plot "$DATADIR/sanders_knheap_test.data" using  (log(\$1)/log(2)):(\$4) title "Cache Level 1", \
     "$DATADIR/sanders_knheap_test.data" using  (log(\$1)/log(2)):(\$5) title "Cache Level 2"
GPLOT