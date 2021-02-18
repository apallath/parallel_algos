/**
 * Demonstration of MPI scan collective.
 * 
 * @author Akash Pallath
 */
#include<mpi.h>
#include<stdio.h>
#include<stdlib.h> //for random
#include<time.h> //for seed

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

    int len = 0;
    char outstr[100];

    len += sprintf(outstr + len, "Array at process %d of %d > ", rank, total);
    for(int i = 0; i < 10; i++){
        len += sprintf(outstr + len, " %d ", a[i]);    
    }    
    printf("%s\n", outstr);

    int b[10];

    //Scan
    //*sendbuf, *recvbuf, count, datatype, op, comm
    MPI_Scan(&a, &b, 10, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    len = 0;

    len += sprintf(outstr + len, "Prefix array at Process %d of %d > ", rank, total);
    for(int i = 0; i < 10; i++){
        len += sprintf(outstr + len, " %d ", b[i]);    
    }    
    printf("%s\n", outstr);

    MPI_Finalize();
}
