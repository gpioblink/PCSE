set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2 pointtype 7 pointsize 1.5
set terminal png
set output 'gcc3.png'
set grid
set xlabel 'data size'
set ylabel 'elapsed time [msec]'
set logscale
plot 'gcc3.dat' with linespoints linestyle 1
