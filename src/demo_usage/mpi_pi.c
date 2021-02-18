/**
 * Distributed memory (MPI) parallel computation of pi.
 * 
 * @author Akash Pallath
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <stdbool.h>

#define REFPI 3.1415926535897932384626433

long double proc_pi(int rank, int total, long long nsteps){
    long long i;
    long double step, sum = 0.0;

    step = 1.0 / ((long double) nsteps);

    long double x;

    for(i = rank; i < nsteps; i+=total){
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    return step * sum;
}

int main(int argc, char* argv[]){ 
    int total, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    long long nsteps;

    if(rank == 0){
        if(argc < 2){
            printf("Required argument: number of steps to compute pi for\n");
            exit(-1);
        }
        nsteps = atoll(argv[1]);
    }

    //Broadcast nsteps to all processors from rank 0
    //*buffer, count, datatype, root, comm
    MPI_Bcast(&nsteps, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    //Each process computes part of the integral into part_pi
    long double part_pi = proc_pi(rank, total, nsteps);

    long double comp_pi;
    //Reduce partial pi values across processors to pi at rank 0
    //*sendbuf, *recvbuf, count, datatype, operation, root, comm
    MPI_Reduce(&part_pi, &comp_pi, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        long double error = fabs(comp_pi - REFPI);
        printf("%lli steps; pi = %.25Lf; error = %.25Lf\n", nsteps, comp_pi, error);
    }

    MPI_Finalize();
}
