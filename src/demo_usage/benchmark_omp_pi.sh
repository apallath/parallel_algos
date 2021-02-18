#!/bin/bash

threadcts=(1 2 4 8 12 16)

#Strong scaling
for th in ${threadcts[@]}
do
  echo "Running $th"
  export OMP_NUM_THREADS=$th
  echo $th >> omp_pi_strong_output.txt
  echo $th >> omp_pi_strong_time.txt
  (time ./demo_omp_pi 10000000000) >> omp_pi_strong_output.txt 2>> omp_pi_strong_time.txt
done

#Weak scaling
for th in ${threadcts[@]}
do
  echo "Running $th"
  export OMP_NUM_THREADS=$th
  echo $th >> omp_pi_weak_output.txt
  echo $th >> omp_pi_weak_time.txt
  steps=$(bc <<< "$th * 1000000000")
  (time ./demo_omp_pi $steps) >> omp_pi_weak_output.txt 2>> omp_pi_weak_time.txt
done
