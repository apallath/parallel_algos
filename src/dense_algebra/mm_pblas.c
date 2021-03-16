/**
 * Distributed memory (MPI) parallel matrix multiplication (with blocking) using PBLAS and PBLACS.
 * 
 * @author Akash Pallath
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include "mkl.h"

int main(int argc, char* argv[]){ 
    int total, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int N;

    if(rank == 0){
        if(argc < 2){
            printf("Required argument: size of random square matrices (each entry is a double between -100 and 100).\n");
            exit(-1);
        }
        N = atoi(argv[1]);
    }

    // Broadcast matrix size to all processors
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // PBLACS init

    // Fill local matrix blocks

    // Blocked parallel matrix multiply

    // Local Frobenius norm

    // Frobenius norm reduction

    // Cleanup
    MPI_Finalize();
}
