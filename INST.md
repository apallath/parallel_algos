## Instructions for OpenMP

Compilation
```
gcc -fopenmp <filename.c> [-o <outname>]
```

Setting runtime variables (e.g. `OMP_NUM_THREADS`, `OMP_WAIT_POLICY`, etc.)
```
export OMP_ENV_VARIABLE="value"
```

## Instructions for OpenMPI

Compilation
```
mpicc <filename.c> [-o <outname>]
```

Run
```
mpirun -np <number_of_processes> <outname>
```
