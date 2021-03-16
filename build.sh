#!/bin/bash

source /opt/intel/oneapi/setvars.sh --force

# Export enviroment variables
export CC=icc
export CXX=icx
export MPICC=mpiicc
export MPICXX=mpiicc

if [ -d "build" ]
then
  rm -r build
fi
mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Debug ..

make -j4
