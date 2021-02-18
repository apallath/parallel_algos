# High performance parallel algorithms

Parallel algorithms implemented using OpenMP and MPI in C.

## Status
[![Open Issues](https://img.shields.io/github/issues-raw/apallath/parallel_algos)](https://github.com/apallath/parallel_algos/issues)
[![Closed Issues](https://img.shields.io/github/issues-closed-raw/apallath/parallel_algos)](https://github.com/apallath/parallel_algos/issues)

## Requirements
- An MPI installation

## Building from source
Customize environment variables in `build.sh`. Generate makefiles and build using CMake by running the script:

```sh
./build.sh
```

## Contents

### Simple OpenMP and MPI demonstration programs (`demo_usage`)
- Demonstrations of point-to-point and collective MPI operations (`demo_usage/mpi_*.c`)
- Parallel pi computation (via integration) in OpenMP and MPI (`demo_usage/{}_pi.c`)

### Dense Linear Algebra function implementations (`dense_algebra`)
- ToDo
