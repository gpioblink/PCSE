#!/bin/bash

# various optimization options
gcc -O0 solve_float_kji.c
./worker.sh float_optimization-O0
gcc -O0 solve_double_kji.c
./worker.sh double_optimization-O0
gcc -O1 solve_float_kji.c
./worker.sh float_optimization-O1
gcc -O1 solve_double_kji.c
./worker.sh double_optimization-O1
gcc -O2 solve_float_kji.c
./worker.sh float_optimization-O2
gcc -O2 solve_double_kji.c
./worker.sh double_optimization-O2

# Different orders of the loop variables for double precision MM
gcc -O2 solve_double_kji.c
./worker.sh double_kji
gcc -O2 solve_double_jki.c
./worker.sh double_jki
gcc -O2 solve_double_ijk.c
./worker.sh double_ijk
