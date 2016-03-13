#!/bin/bash
PLOTOUTPUT=$1
DATADIR='data'

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Running time [seconds]"
set format y "%.1s*10^{%S}"
set yrange  [0.00000000:0.00000060]
set output "$PLOTOUTPUT/InOrder_running_time.eps"

plot "$DATADIR/inOrder_O3_alpha_025.data" using (log(\$1)/log(2)):2 title "Alpha = 0.25", \
     "$DATADIR/inOrder_O3_alpha_050.data" using (log(\$1)/log(2)):2 title "Alpha = 0.50"
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Running time [seconds]"
set format y "%.1s*10^{%S}"
set yrange  [0.00000000:0.00000060]
set output "$PLOTOUTPUT/InOrder_running_time_with_fittings.eps"

plot "$DATADIR/inOrder_O3_alpha_025.data" using (log(\$1)/log(2)):2 title "Alpha = 0.25", \
     "$DATADIR/inOrder_O3_alpha_025.data" using (log(\$1)/log(2)):(10*10**(-9)*log(\$1)/log(2)+2*10**(-9)) title "10*10^{-9}*log(n)" with linespoints, \
     "$DATADIR/inOrder_O3_alpha_025.data" using (log(\$1)/log(2)):(42*10**(-9)*log(\$1)/log(2)-60*10**(-8)) title "42*10^{-9}*log(n)" with linespoints
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
set xlabel "log(n)"
set ylabel "Cache Misses"
set yrange [0:50]
set output "$PLOTOUTPUT/InOrder_cache_misses_with_fittings.eps"

plot "$DATADIR/inOrder_O3_alpha_025.data" using (log(\$1)/log(2)):4 title "L1 Cache, alpha = 0.25", \
     "$DATADIR/inOrder_O3_alpha_025.data" using  (log(\$1)/log(2)):(1.85*log(\$1)/log(2)-22) title "1.85*log(n)" with linespoints, \
     "$DATADIR/inOrder_O3_alpha_025.data" using  (log(\$1)/log(2)):(4.1*log(\$1)/log(2)-67) title "4.1*log(n)" with linespoints, \
     "$DATADIR/inOrder_O3_alpha_025.data" using (log(\$1)/log(2)):5 title "L2 Cache, alpha = 0.25", \
     "$DATADIR/inOrder_O3_alpha_025.data" using  (log(\$1)/log(2)):(2.1*log(\$1)/log(2)-31.5) title "2.1*log(n)" with linespoints, \
     "$DATADIR/inOrder_O3_alpha_025.data" using  (log(\$1)/log(2)):(4.1*log(\$1)/log(2)-72) title "4.1*log(n)" with linespoints


GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "Alpha"
set ylabel "Running time [seconds]"
set format y "%.1s*10^{%S}"
set output "$PLOTOUTPUT/InOrder_different_alpha.eps"

plot "$DATADIR/inOrder_O3_different_alpha.data" using 1:2 title "N = 10^7"
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "Alpha"
set ylabel "Branch Mispridictions"
set output "$PLOTOUTPUT/InOrder_different_alpha_mispredictions.eps"

plot "$DATADIR/inOrder_O3_different_alpha.data" using 1:3 title "N = 10^7"
GPLOT
