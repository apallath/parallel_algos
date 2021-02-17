#!/bin/bash

# Export enviroment variables
export CC=gcc
export CXX=g++
export MPICC=gcc
export MPICXX=g++

if [ -d "build" ]
then
  rm -r build
fi
mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Debug ..

make -j4
