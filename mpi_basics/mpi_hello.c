#include<mpi.h>
#include<stdio.h>

int main(int argc, char* argv[]){ 
    int total, rank;
    MPI_Init(&argc, &argv); //initialize MPI environment
    MPI_Comm_size(MPI_COMM_WORLD, &total);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Hello World from process %d of %d\n", rank, total);
    MPI_Finalize();
}
