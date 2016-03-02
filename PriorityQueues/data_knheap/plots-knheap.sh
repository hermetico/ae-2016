#!/bin/bash
FILE1=$1
FILE2=$2

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Running time"
set format y "%.0s*10^%T"
#set yrange  [0.00000000:0.00000080]
set output "priority_queue_running_time.eps"

plot "${FILE1}" using (log(\$1)/log(2)):(\$2)/(log(\$1)/log(2)) title "Kn heap" with linespoints, \
     "${FILE2}" using (log(\$1)/log(2)):(\$2)/(log(\$1)/log(2)) title "Kn heap adapted" with linespoints
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Branch Mispridictions"
set yrange [0:25]
set output "priority_queue_branch_mispridictions.eps"

plot "${FILE1}" using  (log(\$1)/log(2)):(\$3)/(log(\$1)/log(2)) title "Kn heap" with linespoints, \
     "${FILE2}" using (log(\$1)/log(2)):(\$3)/(log(\$1)/log(2)) title  "Kn heap adapted" with linespoints
GPLOT

gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "Level 1 Data Cache Misses"
#set yrange [0:50]
set output "priority_queue_cache_misses_level_1.eps"

plot "${FILE1}" using  (log(\$1)/log(2)):4 title "Kn heap" with linespoints, \
     "${FILE2}"  using (log(\$1)/log(2)):4 title "Kn heap adapted" with linespoints
GPLOT



gnuplot << GPLOT
set terminal postscript eps enhanced color
#set logscale x
set xlabel "log(n)"
set ylabel "L2 Data Cache Misses"
#set yrange [0:50]
set output "priority_queue_cache_misses_level_2.eps"

plot "${FILE1}" using  (log(\$1)/log(2)):5 title "Kn heap" with linespoints, \
     "${FILE2}"  using (log(\$1)/log(2)):5 title "Kn heap adapted" with linespoints
GPLOT


