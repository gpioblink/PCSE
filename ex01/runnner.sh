#!/bin/bash
gcc q1a.c
./worker.sh
gcc -O0 q1a.c
./worker.sh gcc0
gcc -O1 q1a.c
./worker.sh gcc1
gcc -O2 q1a.c
./worker.sh gcc2
gcc -O3 q1a.c
./worker.sh gcc3