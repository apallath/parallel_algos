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

    int b[10];
    
    //Scan
    MPI_Scan(&b, &bpref, 10, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    len = 0;
    len += sprintf(outbuf + len, "Prefix Array at Process %d of %d > ", rank, total);
    for(int i = 0; i < 10; i++){
        len += sprintf(outbuf + len, " %d ", bpref[i]);    
    }    
    printf("%s\n", outbuf);

    MPI_Barrier(MPI_COMM_WORLD);

    //Demo - Scatter and Gather
    //First, we generate data
    int* alldata = NULL;
    alldata = (int*) malloc(2 * total * sizeof(int));
    int data[2];
    if(rank == 0){
        printf("Data generated at 0 > ");
        for(int i = 0; i < 2*total; i++){
            alldata[i] = rand() % 97 ;
            printf("%d ", alldata[i]);
        }
        printf("\n");
    }        
    //Now, scatter to all nodes, chunk size 2
    MPI_Scatter(alldata, 2, MPI_INT, data, 2, MPI_INT, 0, MPI_COMM_WORLD);  
    //Modify data
    data[0] *= (rank+1); 
    data[1] *= (rank+1);
    //Check
    printf("Data at [%d] > [%d] [%d]\n", rank, data[0], data[1]);    
    //Now, gather at last node
    MPI_Gather(data, 2, MPI_INT, alldata, 2, MPI_INT, total-1, MPI_COMM_WORLD);
    //Check
    if(rank == total - 1){
        printf("Data recieved at %d > ", total - 1);
        for(int i = 0; i < 2*total; i++){
            printf("%d ", alldata[i]);
        }
        printf("\n");
    }

    //End
    MPI_Finalize();
}
