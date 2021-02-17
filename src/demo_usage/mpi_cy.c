/**
 * Demonstration of MPI P2P communication using MPI_Sendrecv.
 * Performs a cyclic shift amongst processes. Each process sends its array to its next nearest
 * neighbor and recieves its previous nearest neighbor's array.
 * 
 * @author Akash Pallath
 */
#include<mpi.h>
#include<stdio.h>

int main(int argc, char* argv[]){
    int total, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int a[5], b[5];  

    //different computation for different processes
    for(int i = 0; i < 5; i++) {
        a[i] = (rank + 1)*i*i;
    }
    printf("(Before Cyclic Shift) Process %d of %d : %d %d %d %d %d\n", rank, total, a[0], a[1], a[2], a[3], a[4]);

    MPI_Status st;

    //*sendbuf, sendcount, sendtype, dest, sendtag, *recvbuf, recvcount, recvtype, source, recvtag, comm, status
    MPI_Sendrecv(&a, 5, MPI_INT, (rank+1)%total, 1, &b, 5, MPI_INT, (rank-1+total)%total, MPI_ANY_TAG, MPI_COMM_WORLD, &st);

    for(int i = 0; i < 5; i++) {
        a[i] = b[i];
    }
    printf("(After Cyclic Shift) Process %d of %d : %d %d %d %d %d\n", rank, total, a[0], a[1], a[2], a[3], a[4]);

    MPI_Finalize();
}
