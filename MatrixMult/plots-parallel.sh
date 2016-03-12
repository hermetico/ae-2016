#!/bin/bash
DATADIR=$1
PLOTOUTPUT=$2


mkdir -p $PLOTOUTPUT

gnuplot << GPLOT
set terminal postscript eps enhanced color
set xlabel "log(n)"
set ylabel "Seconds"
set format y "%.0s*10^%T"
set output "$PLOTOUTPUT/running_time.eps"

plot    "$DATADIR/recmult_1_thread.data" using (log(\$1)/log(2)):(log(\$2)/log(2)) title "RecMult 1 thread", \
        "$DATADIR/recmult_2_threads.data" using (log(\$1)/log(2)):(log(\$2)/log(2)) title "RecMult 2 threads", \
        "$DATADIR/recmult_4_threads.data" using (log(\$1)/log(2)):(log(\$2)/log(2)) title "RecMult 4 threads", \
        "$DATADIR/recmult_8_threads.data" using (log(\$1)/log(2)):(log(\$2)/log(2)) title "RecMult 8 threads"
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
set xlabel "log(n)"
set ylabel "Branch Mispridictions"
set output "$PLOTOUTPUT/branch_mispredictions.eps"

plot    "$DATADIR/recmult_1_thread.data" using (log(\$1)/log(2)):(log(\$3)/log(2)) title "RecMult 1 thread", \
        "$DATADIR/recmult_2_threads.data" using (log(\$1)/log(2)):(log(\$3)/log(2)) title "RecMult 2 threads", \
        "$DATADIR/recmult_4_threads.data" using (log(\$1)/log(2)):(log(\$3)/log(2)) title "RecMult 4 threads", \
        "$DATADIR/recmult_8_threads.data" using (log(\$1)/log(2)):(log(\$3)/log(2)) title "RecMult 8 threads"
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
set xlabel "log(n)"
set ylabel "Level 1 Cache Misses"
set output "$PLOTOUTPUT/l1_cache_misses.eps"

plot    "$DATADIR/recmult_1_thread.data" using (log(\$1)/log(2)):(log(\$4)/log(2)) title "RecMult 1 thread", \
        "$DATADIR/recmult_2_threads.data" using (log(\$1)/log(2)):(log(\$4)/log(2)) title "RecMult 2 threads", \
        "$DATADIR/recmult_4_threads.data" using (log(\$1)/log(2)):(log(\$4)/log(2)) title "RecMult 4 threads", \
        "$DATADIR/recmult_8_threads.data" using (log(\$1)/log(2)):(log(\$4)/log(2)) title "RecMult 8 threads"
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
set xlabel "log(n)"
set ylabel "Level 2 Cache Misses"
set output "$PLOTOUTPUT/l2_cache_misses.eps"

plot    "$DATADIR/recmult_1_thread.data" using (log(\$1)/log(2)):(log(\$5)/log(2)) title "RecMult 1 thread", \
        "$DATADIR/recmult_2_threads.data" using (log(\$1)/log(2)):(log(\$5)/log(2)) title "RecMult 2 threads", \
        "$DATADIR/recmult_4_threads.data" using (log(\$1)/log(2)):(log(\$5)/log(2)) title "RecMult 4 threads", \
        "$DATADIR/recmult_8_threads.data" using (log(\$1)/log(2)):(log(\$5)/log(2)) title "RecMult 8 threads"
GPLOT