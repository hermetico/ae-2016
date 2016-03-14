#!/bin/bash
DATADIR=$1
PLOTOUTPUT=$2


mkdir -p $PLOTOUTPUT

gnuplot << GPLOT
set terminal postscript eps enhanced color
set xlabel "log(n)"
set ylabel "Seconds"
set format y "%.0s*10^%T"
set output "$PLOTOUTPUT/recmult_extended_running_time.eps"

plot    "$DATADIR/recmult_0.data" using (log(\$1)/log(2)):(log(\$2)/log(2)) title "RecMult limit 0", \
        "$DATADIR/recmult_8.data" using (log(\$1)/log(2)):(log(\$2)/log(2)) title "RecMult limit 8", \
        "$DATADIR/recmult_16.data" using (log(\$1)/log(2)):(log(\$2)/log(2)) title "RecMult limit 16", \
        "$DATADIR/recmult_32.data" using (log(\$1)/log(2)):(log(\$2)/log(2)) title "RecMult limit 32", \
        "$DATADIR/recmult_40.data" using (log(\$1)/log(2)):(log(\$2)/log(2)) title "RecMult limit 40", \
        "$DATADIR/recmult_64.data" using (log(\$1)/log(2)):(log(\$2)/log(2)) title "RecMult limit 64"
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
set xlabel "log(n)"
set ylabel "Level 1 Cache Misses"
set output "$PLOTOUTPUT/l1_cache_misses.eps"

plot    "$DATADIR/recmult_0.data" using (log(\$1)/log(2)):(log(\$4)/log(2)) title "RecMult limit 0", \
        "$DATADIR/recmult_8.data" using (log(\$1)/log(2)):(log(\$4)/log(2)) title "RecMult limit 8", \
        "$DATADIR/recmult_16.data" using (log(\$1)/log(2)):(log(\$4)/log(2)) title "RecMult limit 16", \
        "$DATADIR/recmult_32.data" using (log(\$1)/log(2)):(log(\$4)/log(2)) title "RecMult limit 32", \
        "$DATADIR/recmult_40.data" using (log(\$1)/log(2)):(log(\$4)/log(2)) title "RecMult limit 40", \
        "$DATADIR/recmult_64.data" using (log(\$1)/log(2)):(log(\$4)/log(2)) title "RecMult limit 64"
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
set xlabel "log(n)"
set ylabel "Level 2 Cache Misses"
set output "$PLOTOUTPUT/l2_cache_misses.eps"

plot    "$DATADIR/recmult_0.data" using (log(\$1)/log(2)):(log(\$5)/log(2)) title "RecMult limit 0", \
        "$DATADIR/recmult_8.data" using (log(\$1)/log(2)):(log(\$5)/log(2)) title "RecMult limit 8", \
        "$DATADIR/recmult_16.data" using (log(\$1)/log(2)):(log(\$5)/log(2)) title "RecMult limit 16", \
        "$DATADIR/recmult_32.data" using (log(\$1)/log(2)):(log(\$5)/log(2)) title "RecMult limit 32", \
        "$DATADIR/recmult_40.data" using (log(\$1)/log(2)):(log(\$5)/log(2)) title "RecMult limit 40", \
        "$DATADIR/recmult_64.data" using (log(\$1)/log(2)):(log(\$5)/log(2)) title "RecMult limit 64"
GPLOT