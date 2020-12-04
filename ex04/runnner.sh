#!/bin/bash

# Evaluate the performance for matrices as float and double precisions.
gcc solve_block_float_ijk.c
#./worker.sh float_block_8 5 8
#./worker.sh float_block_16 5 16
#./worker.sh float_block_32 5 32
#./worker.sh float_block_64 5 64
./worker.sh float_block_128 5 128
./worker.sh float_block_256 5 256
./worker.sh float_block_512 5 512
./worker.sh float_block_1024 5 1024
./worker.sh float_block_2048 5 2048
gcc solve_block_double_ijk.c
./worker.sh double_block_8 5 8
./worker.sh double_block_16 5 16
./worker.sh double_block_32 5 32
./worker.sh double_block_64 5 64
./worker.sh double_block_128 5 128
./worker.sh double_block_256 5 256
./worker.sh double_block_512 5 512
./worker.sh double_block_1024 5 1024
./worker.sh double_block_2048 5 2048
