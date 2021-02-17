/**
 * Demonstration of MPI reduction collective.
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

    //Each process computes array values
    int a[10];
    for(int i = 0; i < 10; i++){ //Generate data at each processor
        a[i] = (rank + 1) * (i + 1);
    }   

    char outstr[1000]; //Build an output string and output to stdout in one go
    int len = 0;
                // pointer location at outstr beginning + len
    len += sprintf(outstr + len, "At Process %d of %d > ", rank, total);
    for(int i = 0; i < 10; i++){
        len += sprintf(outstr + len, " %d ", a[i]);    
    }    
    printf("%s\n", outstr);

    int b[10]; //Array to reduce to

    //Reduce, root (process 0) has reduced value
    //*sendbuf, *recvbuf, count, datatype, operation, root, comm
    MPI_Reduce(&a, &b, 10, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("Result of Reduction at %d > ", rank);
        for(int i = 0; i < 10; i++){
            printf("%d ", b[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
}
