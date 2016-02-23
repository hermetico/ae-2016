#!/bin/bash
PLOTOUTPUT=$1
DATADIR='data'

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Running time"
set format y "%.0s*10^%T"
set yrange  [0.00000000:0.00000080]
set output "$PLOTOUTPUT/InOrder_running_time.eps"

plot "$DATADIR/inOrder_O3_alpha_025.data" using (log(\$1)/log(2)):2 title "Alpha = 0.25", \
     "$DATADIR/inOrder_O3_alpha_050.data" using (log(\$1)/log(2)):2 title "Alpha = 0.50"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Branch Mispridictions/log(n)"
set yrange [0:1]
set output "$PLOTOUTPUT/InOrder_branch_mispredictions.eps"

plot "$DATADIR/inOrder_O3_alpha_025.data" using (log(\$1)/log(2)):(\$3/(log(\$1)/log(2))) title "Alpha = 0.25", \
     "$DATADIR/inOrder_O3_alpha_050.data" using (log(\$1)/log(2)):(\$3/(log(\$1)/log(2))) title "Alpha = 0.50"
GPLOT


gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Cache Misses"
set yrange [0:50]
set output "$PLOTOUTPUT/InOrder_cache_misses.eps"

plot "$DATADIR/inOrder_O3_alpha_025.data" using (log(\$1)/log(2)):4 title "L1 Cache, alpha = 0.25", \
     "$DATADIR/inOrder_O3_alpha_025.data" using (log(\$1)/log(2)):5 title "L2 Cache, alpha = 0.25", \
     "$DATADIR/inOrder_O3_alpha_050.data" using (log(\$1)/log(2)):4 title "L1 Cache, alpha = 0.50", \
     "$DATADIR/inOrder_O3_alpha_050.data" using (log(\$1)/log(2)):5 title "L2 Cache, alpha = 0.50"
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "alpha"
set ylabel "Running time"
set format y "%.0s*10^%T"
set output "$PLOTOUTPUT/InOrder_different_alpha.eps"

plot "$DATADIR/inOrder_O3_different_alpha.data" using 1:2 title "N = 10^7"
GPLOT
