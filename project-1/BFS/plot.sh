g++ -O3 main.cpp -o bfs
./bfs i > data/bfs_O3_vector_iterative.data
./bfs > data/bfs_O3_vector_recursive.data

gnuplot << GPLOT
set terminal postscript eps enhanced color
set logscale x
set xlabel "N"
set ylabel "Running time"
set output "data/test.eps"
plot "data/bfs_O3_vector_recursive.data" title "BFS -O3 Recursive", "data/bfs_O3_vector_iterative.data" title "BFS -O3 Iterative"
GPLOT

#rm data/bfs_O3_vector_iterative.data
#rm data/bfs_O3_vector_recursive.data

open "data/test.eps"