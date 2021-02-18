#!/bin/bash

proccts=(1 2 4 8 12 16)

#Strong scaling
for p in ${proccts[@]}
do
  echo "Running strong $p"
  echo $p >> mpi_pi_strong_output.txt
  echo $p >> mpi_pi_strong_time.txt
  (time mpirun -np $p --use-hwthread-cpus demo_mpi_pi 10000000000) >> mpi_pi_strong_output.txt 2>> mpi_pi_strong_time.txt
done

#Weak scaling
for p in ${proccts[@]}
do
  echo "Running weak $p"
  echo $p >> mpi_pi_weak_output.txt
  echo $p >> mpi_pi_weak_time.txt
  steps=$(bc <<< "$p * 1000000000")
  (time mpirun -np $p --use-hwthread-cpus demo_mpi_pi $steps) >> mpi_pi_weak_output.txt 2>> mpi_pi_weak_time.txt
done
