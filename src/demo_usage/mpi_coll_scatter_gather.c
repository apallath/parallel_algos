/**
 * Demonstration of MPI scatter and gather collectives.
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

    //Initial array of length 2 * nprocs
    int* initdata = NULL;
    initdata = (int*) malloc(2 * total * sizeof(int));

    //Gathered (modified) data
    int* gathdata = NULL;
    gathdata = (int*) malloc(2 * total * sizeof(int));

    int len = 0;
    char outstr[100];

    if(rank == 0){
        //Generate and print
        srand((unsigned int) time(NULL));
        len += sprintf(outstr + len, "Data generated at %d> ", rank);
        for(int i = 0; i < 2 * total; i++){
            initdata[i] = rand() % 97 ;
            len += sprintf(outstr + len, "%d ", initdata[i]);
        }
        printf("%s\n", outstr);
    }        

    int data[2];

    //Scatter to all procs with chunk size 2
    //*sendbuf, sendcount, sendtype, *recvbuf, recvcount, recvtype, root, comm
    MPI_Scatter(initdata, 2, MPI_INT, &data, 2, MPI_INT, 0, MPI_COMM_WORLD);  

    //Modify data
    data[0] *= (rank + 1); 
    data[1] *= (rank + 1);

    //Check
    printf("Data modified at %d > [%d %d] to [%d %d]\n", rank, data[0]/(rank + 1), data[1]/(rank + 1), data[0], data[1]);    

    //Now, gather at 0
    //*sendbuf, sendcount, sendtype, *recvbuf, recvcount, recvtype, root, comm
    MPI_Gather(&data, 2, MPI_INT, gathdata, 2, MPI_INT, 0, MPI_COMM_WORLD);

    //Check
    if(rank == 0){
        len = 0;

        len += sprintf(outstr + len, "Data gathered at %d > ", rank);
        for(int i = 0; i < 2*total; i++){
            len += sprintf(outstr + len, "%d ", gathdata[i]);
        }
        printf("%s\n", outstr);
    }

    //End
    MPI_Finalize();
}
