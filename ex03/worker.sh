#!/bin/bash

OUTPUT_NAME=${1:-data}
N=${2:-5}
echo "0 0" > $OUTPUT_NAME.dat

for i in 8 16 32 64 128 256 512 1024 2048
do

sum=0

for j in `seq $N`
do

result=`./a.out $i`
time=`echo $result | awk '{print $5}'`
sum=`echo "scale=10; $time + $sum" | bc`
echo $result

done

ave=`echo "scale=10; $sum / $N" | bc`
mflops=`echo "scale=10; (2*$i^3)/($ave)/(1.0*10^6)" | bc`
echo "***" ave for $i is $mflops in mflops "***"
echo $i $mflops >> $OUTPUT_NAME.dat
done

echo "set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2 pointtype 7 pointsize 1.5" > tmp.plt
echo "set terminal png" >> tmp.plt
echo "set output '$OUTPUT_NAME.png'" >> tmp.plt

echo "set grid" >> tmp.plt
echo "set xlabel 'matrix size N'" >> tmp.plt
echo "set ylabel 'mega floating operations per second [MFLOPS]'" >> tmp.plt
echo "set logscale" >> tmp.plt
echo "plot '$OUTPUT_NAME.dat' with linespoints linestyle 1" >> tmp.plt

gnuplot tmp.plt
rm -f tmp.plt