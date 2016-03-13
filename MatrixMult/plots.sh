#!/bin/bash
DATADIR=$1
PLOTOUTPUT=$2


mkdir -p $PLOTOUTPUT

################ Simple matrix mult

gnuplot << GPLOT
set terminal postscript eps enhanced color
set xlabel "log(n)"
set ylabel "log(Seconds)"
set format y "%.0s*10^%T"
set output "$PLOTOUTPUT/simple_mult_running_time.eps"

plot "$DATADIR/simplemult.data" using (log(\$1)/log(2)):(log(\$2)/log(2)) title "SimpleMult" with linespoints

GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
set xlabel "log(n)"
set ylabel "log(Level 1 Cache Misses)"
set output "$PLOTOUTPUT/simple_mult_l1_cache_misses.eps"

plot "$DATADIR/simplemult.data" using (log(\$1)/log(2)):(log(\$4)/log(2)) title "SimpleMult" with linespoints
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
set xlabel "log(n)"
set ylabel "log(Level 2 Cache Misses)"
set output "$PLOTOUTPUT/simple_mult_l2_cache_misses.eps"

plot "$DATADIR/simplemult.data" using (log(\$1)/log(2)):(log(\$5)/log(2)) title "SimpleMult" with linespoints
GPLOT

################ PLOTS RECTMULT

gnuplot << GPLOT
set terminal postscript eps enhanced color
set xlabel "log(n)"
set ylabel "log(Seconds)"
set format y "%.0s*10^%T"
set output "$PLOTOUTPUT/recmult_running_time.eps"

plot "$DATADIR/recmult.data" using (log(\$1)/log(2)):(log(\$2)/log(2)) title "RecMult"  with linespoints

GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
set xlabel "log(n)"
set ylabel "log(Level 1 Cache Misses)"
set output "$PLOTOUTPUT/recmult_l1_cache_misses.eps"

plots "$DATADIR/recmult.data" using (log(\$1)/log(2)):(log(\$4)/log(2)) title "RecMult" with linespoints
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
set xlabel "log(n)"
set ylabel "log(Level 2 Cache Misses)"
set output "$PLOTOUTPUT/recmult_l2_cache_misses.eps"

plot "$DATADIR/recmult.data" using (log(\$1)/log(2)):(log(\$5)/log(2)) title "RecMult" with linespoints
GPLOT


###########

gnuplot << GPLOT
set terminal postscript eps enhanced color
set xlabel "log(n)"
set ylabel "log(Seconds)"
set format y "%.0s*10^%T"
set output "$PLOTOUTPUT/running_time.eps"

plot "$DATADIR/simplemult.data" using (log(\$1)/log(2)):(\$2/(\$1*\$1*\$1)) title "SimpleMult" with linespoints,\
     "$DATADIR/tiledmult.data" using (log(\$1)/log(2)):(\$2/(\$1*\$1*\$1)) title "TiledMult" with linespoints,\
     "$DATADIR/recmult.data" using (log(\$1)/log(2)):(\$2/(\$1*\$1*\$1)) title "RecMult"  with linespoints,

GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
set xlabel "log(n)"
set ylabel "log(Branch Mispridictions)"
set output "$PLOTOUTPUT/branch_mispredictions.eps"

plot "$DATADIR/simplemult.data" using (log(\$1)/log(2)):(log(\$3)/log(2)) title "SimpleMult" with linespoints,\
     "$DATADIR/tiledmult.data" using (log(\$1)/log(2)):(log(\$3)/log(2)) title "TiledMult" with linespoints,\
     "$DATADIR/recmult.data" using (log(\$1)/log(2)):(log(\$3)/log(2)) title "RecMult" with linespoints
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
set xlabel "log(n)"
set ylabel "log(Level 1 Cache Misses)"
set output "$PLOTOUTPUT/l1_cache_misses.eps"

plot "$DATADIR/simplemult.data" using (log(\$1)/log(2)):(log(\$4)/log(2)) title "SimpleMult" with linespoints,\
     "$DATADIR/tiledmult.data" using (log(\$1)/log(2)):(log(\$4)/log(2)) title "TiledMult" with linespoints,\
     "$DATADIR/recmult.data" using (log(\$1)/log(2)):(log(\$4)/log(2)) title "RecMult" with linespoints
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
set xlabel "log(n)"
set ylabel "log(Level 2 Cache Misses)"
set output "$PLOTOUTPUT/l2_cache_misses.eps"

plot "$DATADIR/simplemult.data" using (log(\$1)/log(2)):(log(\$5)/log(2)) title "SimpleMult" with linespoints,\
     "$DATADIR/tiledmult.data" using (log(\$1)/log(2)):(log(\$5)/log(2)) title "TiledMult" with linespoints,\
     "$DATADIR/recmult.data" using (log(\$1)/log(2)):(log(\$5)/log(2)) title "RecMult" with linespoints
GPLOT