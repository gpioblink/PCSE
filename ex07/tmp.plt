set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2 pointtype 7 pointsize 1.5
set terminal png
set output 'data.png'
set grid
set xlabel 'Number of Processors N'
set ylabel 'elapsed time [msec]'
plot 'data.dat' with linespoints linestyle 1
