/**
 * Demonstration of MPI broadcast collective.
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

    //Demo - Broadcast collective
    int a[10];

    if(rank == 0){ //compute values of a at 0
        srand((unsigned int) time(NULL));
        for(int i = 0; i < 10; i++){
            a[i] = rand() % 97;                  
        }
    }
    //Broadcast
    //*buffer, count, datatype, root, comm
    MPI_Bcast(&a, 10, MPI_INT, 0, MPI_COMM_WORLD);

    //Check
    char outstr[1000]; //Build an output string and output to stdout in one go
    int len = 0;
                // pointer location at outstr beginning + len
    len += sprintf(outstr + len, "At Process %d of %d > ", rank, total);
    for(int i = 0; i < 10; i++){
        len += sprintf(outstr + len, " %d ", a[i]);    
    }    
    printf("%s\n", outstr);

    MPI_Finalize();
}
