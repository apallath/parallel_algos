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
    if(rank == 0){ //computation at 0
        srand((unsigned int) time(NULL));
        for(int i = 0; i < 10; i++){
            a[i] = rand() % 97;                  
        }
    }
    //Broadcast
    MPI_Bcast(&a, 10, MPI_INT, 0, MPI_COMM_WORLD);
    //Check
    char outbuf[1000];
    int len = 0;
    len += sprintf(outbuf + len, "At Process %d of %d > ", rank, total);
    for(int i = 0; i < 10; i++){
        len += sprintf(outbuf + len, " %d ", a[i]);    
    }    
    printf("%s\n", outbuf);

    //For reduction and prefix collectives
    int b[10];
    for(int i = 0; i < 10; i++){ //Generate data at each processor
        b[i] = (rank + 1)*(i + 1);
    }   
    
    //Demo - Reduction collective
    int bred[10]; //all processes must provide recvbuf
    //Reduce
    MPI_Reduce(&b, &bred, 10, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank == 0){
        printf("Result of Reduction > ");
        for(int i = 0; i < 10; i++){
            printf("%d ", bred[i]);
        }
        printf("\n");
    }

    //Demo - Scan
    int bpref[10];
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
