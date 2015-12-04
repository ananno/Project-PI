#!/bin/bash

echo "Running serial code...";
time ./makepi_serial_1B.x;
echo

for n in 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192;
do
	echo "Running parallel code with thread $n ...";
	time ./makepi_omp_1B_"$n"T.x;
	echo
done

exit
