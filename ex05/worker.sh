#!/bin/bash

OUTPUT_NAME=${1:-data}
NPROC=${2:-1}
N=${3:-10}
echo "0 0" > $OUTPUT_NAME.dat

TIMEFORMAT="%R"

for i in 1000 10000 100000
do

sum=0

for j in `seq $N`
do

time=`(time mpirun -np $NPROC ./pi $i > /dev/null 2>&1 ) 2>&1`
sum=`echo "scale=10; $time + $sum" | bc`
echo $time

done

ave=`echo "scale=10; $sum / $N" | bc`
echo "***" ave for $i is $ave "***"
echo $i $ave >> $OUTPUT_NAME.dat
done

echo "set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2 pointtype 7 pointsize 1.5" > tmp.plt
echo "set terminal png" >> tmp.plt
echo "set output '$OUTPUT_NAME.png'" >> tmp.plt

echo "set grid" >> tmp.plt
echo "set xlabel 'number of divisions in the numerical integration x 1000'" >> tmp.plt
echo "set ylabel 'elapsed time [sec]'" >> tmp.plt
echo "set logscale" >> tmp.plt
echo "plot '$OUTPUT_NAME.dat' with linespoints linestyle 1" >> tmp.plt

gnuplot tmp.plt
rm -f tmp.plt
