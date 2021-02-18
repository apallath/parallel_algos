#!/bin/bash

threadcts=(1 2 4 8 12 16)

#Strong scaling
for th in ${threadcts[@]}
do
  echo "Running $th"
  export OMP_NUM_THREADS=$th
  echo $th >> outputs.sh
  echo $th >> times.sh
  (time ./demo_omp_pi 1000000000) >> strong_output.sh 2>> strong_time.sh
done

#Weak scaling
for th in ${threadcts[@]}
do
  echo "Running $th"
  export OMP_NUM_THREADS=$th
  echo $th >> outputs.sh
  echo $th >> times.sh
  steps=$(bc <<< "$th * 100000000")
  (time ./demo_omp_pi $steps) >> weak_output.sh 2>> weak_time.sh
done
