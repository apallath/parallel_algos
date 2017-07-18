#include<mpi.h>
#include<stdio.h>
#include<math.h>

#define PUTBARRIER

int main(int argc, char* argv[]){
    int total, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int a[5], b[5];  
    //different computation for different processes
    for(int i = 0; i < 5; i++) a[i] = rank*i*i;
    printf("(Before Cyclic Shift) Process[%d] of [%d] : [%d][%d][%d][%d][%d]\n", rank, total, a[0], a[1], a[2], a[3], a[4]);
    //wlog let tag = 1
    MPI_Status st;
    MPI_Sendrecv(&a, 5, MPI_INT, (rank+1)%total, 1, b, 5, MPI_INT, (rank-1+total)%total, 1, MPI_COMM_WORLD, &st);

    #ifdef PUTBARRIER
    //print only after the shift - to separate print operations before and after
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank == 0) printf("------\n"); //only root process execs this
    MPI_Barrier(MPI_COMM_WORLD);
    #endif

    for(int i = 0; i < 5; i++) a[i] = b[i];
    printf("(After Cyclic Shift) Process[%d] of [%d] : [%d][%d][%d][%d][%d]\n", rank, total, a[0], a[1], a[2], a[3], a[4]);
    MPI_Finalize();
}
