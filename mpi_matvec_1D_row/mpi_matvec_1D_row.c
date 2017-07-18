//1D Matrix-Vector
#include<stdio.h>
#include<stdlib.h> //for malloc
#include<mpi.h>

//Master-slave model. Master performs IO and distributes matrix among slaves.
//Matrix-vector product : A * b = x

int main(int argc, char *argv[]){
    //--------------------Variables declaration--------------------//
    int np, rank, i, j, nrows;
    double *A, *A_loc;
    /*  The matrix is stored in row-major format. 
        The MPI scatter collective requires matrix elements to be stored in a contiguous fashion.
        Cannot ensure this with a multidimensional dynamically allocated array. */
    double *b, *x, *x_loc;    
    int n;
    //--------------------MPI Env Mgmt-----------------------------//
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);    
    //--------------------IO, Mem-alloc, Dist----------------------//
    if(rank == 0){
        scanf("%d", &n);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD); //all processes now know n

    nrows = n / np;
    A = (double*) malloc(n*n*sizeof(double));    
    b = (double*) malloc(n*sizeof(double));    
    x = (double*) malloc(n*sizeof(double));
    A_loc = (double*) malloc(nrows*n*sizeof(double)); //on each process, after scatter
    x_loc = (double*) malloc(nrows*sizeof(double)); //on each process, before gather
    if(rank == 0){ //IO
        //mat
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                scanf("%lf", &A[i*n + j]);            
            }
        }
        //vec
        for(i = 0; i < n; i++){
            scanf("%lf", &b[i]);        
        }         
    }   
    MPI_Barrier(MPI_COMM_WORLD);  
    MPI_Bcast(b, n, MPI_DOUBLE, 0, MPI_COMM_WORLD); //all processes have the entire vector
    MPI_Scatter(A, n*nrows, MPI_DOUBLE, A_loc, n*nrows, MPI_DOUBLE, 0, MPI_COMM_WORLD); //scatter nrows rows of A among the processes
    //--------------------Compute----------------------------------//
    for(int i = 0; i < nrows; i++){
        x_loc[i] = 0.0;
        for(int j = 0; j < n; j++){
            x_loc[i] += A_loc[i*n + j] * b[j];            
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    //--------------------Gather and output -----------------------//
    MPI_Gather(x_loc, nrows, MPI_DOUBLE, x, nrows, MPI_DOUBLE, 0, MPI_COMM_WORLD); //gather result
    if(rank == 0){ //IO
        for(i = 0; i < n; i++){
            printf("%lf ", x[i]);
        }
        printf("\n");
    }
    //--------------------Finalize---------------------------------//
    MPI_Finalize();
}
