#!/bin/bash

OUTPUT_NAME=${1:-data}
N=${2:-5}
echo "" > $OUTPUT_NAME.dat

echo "[$OUTPUT_NAME]"

for i in 1 2 3 4 5 6 7 8
do
sumall=0

for j in `seq $N`
do

mpirun -np $i ./a.out 100000 2> /dev/null | grep sec > tmp.txt
sum=0
while read line
do
  time=`echo $line | awk '{print $5}'`
  echo $time 
  sum=`echo "scale=10; $time + $sum" | bc`
done < tmp.txt
echo "+++"
seqsum=`echo "scale=10; $sum / $i" | bc`
echo $seqsum
sumall=`echo "scale=10; $seqsum + $sumall" | bc`
echo "---"
done

ave=`echo "scale=10; $sumall / $N" | bc`
echo "***" ave for $i is $ave in mflops "***"
echo $i $ave >> $OUTPUT_NAME.dat

done

echo "set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2 pointtype 7 pointsize 1.5" > tmp.plt
echo "set terminal png" >> tmp.plt
echo "set output '$OUTPUT_NAME.png'" >> tmp.plt

echo "set grid" >> tmp.plt
echo "set xlabel 'Number of Processors N'" >> tmp.plt
echo "set ylabel 'elapsed time [msec]'" >> tmp.plt
echo "plot '$OUTPUT_NAME.dat' with linespoints linestyle 1" >> tmp.plt

gnuplot tmp.plt

