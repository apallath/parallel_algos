#include<mpi.h>
#include<stdio.h>
#include<math.h>

//Transmit data around in a ring, modifying it at each node/process.
//Stop after the data reaches back to the root node/process.
int main(int argc, char* argv[]){
    int a = 1;
    int total, rank;
    MPI_Init(&argc, &argv);
    MPI_Status st;
    MPI_Comm_size(MPI_COMM_WORLD, &total);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == 0){
        //tag = 1
        MPI_Send(&a, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
    }
    int b,addb;
    MPI_Recv(&b, 1, MPI_INT, (rank - 1 + total) % total, 1, MPI_COMM_WORLD, &st);  
    printf("Recieved %d at node %d from node %d\n", b, rank, st.MPI_SOURCE);  
    if(rank == 0){
        printf("Terminated with value %d\n", b);
    }
    else{        
        addb = 1<<(rank+1);
        printf("Added %d at node %d\n", addb, rank);
        b+=addb;
        MPI_Send(&b, 1, MPI_INT, (rank + 1) % total, 1, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}
        
