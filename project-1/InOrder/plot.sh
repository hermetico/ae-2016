#!/bin/bash
PLOTOUTPUT=$1
DATADIR='data'

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Running time"
set format y "%.0s*10^%T"
#set yrange  [0.00000002:0.00000025]
set output "$PLOTOUTPUT/InOrder_running_time.eps"

plot "$DATADIR/inOrder_O3_constant_alpha.data" using (log(\$1)/log(2)):(\$2) title "In Order -O3"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Branch Mispridictions/log(n)"
set yrange [0:1.5]
set output "$PLOTOUTPUT/InOrder_branch_mispredictions.eps"

plot "$DATADIR/inOrder_O3_constant_alpha.data" using (log(\$1)/log(2)):(\$3/(log(\$1)/log(2))) title "In Order -O3"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Cache Misses"
#set yrange [0:30]
set output "$PLOTOUTPUT/InOrder_cache_misses.eps"

plot "$DATADIR/inOrder_O3_constant_alpha.data" using (log(\$1)/log(2)):4 title "In Order -O3: L1 Cache", \
     "$DATADIR/inOrder_O3_constant_alpha.data" using (log(\$1)/log(2)):5 title "In Order -O3: L2 Cache"
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "alpha"
set ylabel "Running time"
set format y "%.0s*10^%T"
set output "$PLOTOUTPUT/InOrder_different_alpha.eps"

plot "$DATADIR/inOrder_O3_different_alpha.data" using 1:2 title "In Order -O3"
GPLOT
