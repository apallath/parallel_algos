/**
 * Matrix multiplication using MKL BLAS. Shared-memory (OpenMP) parallelism through MKL BLAS implementation.
 * Set the value of the MKL_NUM_THREADS environment variable to tune OpenMP parallelism.
 * 
 * @author Akash Pallath
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mkl.h"

void fill(double* data, int N, int scale)
{
    for (int i = 0; i < N * N; i++){
        data[i] = 2 * scale * drand48() - scale; // Uniformly distributed over [-scale, scale]
    }
}

void square_dgemm(int N, double* A, double* B, double* C){
    /** Calls CBLAS DGEMM
     * See Intel MKL documentation for interface reference
     */
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1, A, N, B, N, 0, C, N);
}

int main(int argc, char* argv[]){ 
    int N;
    if(argc < 2){
        printf("Required argument: size of random square matrices (each entry is a double between -100 and 100).\n");
        exit(-1);
    }
    N = atoi(argv[1]);

    // Allocate memory for all matrices
    double* A = (double*) malloc(N * N * sizeof(double));
    double* B = (double*) malloc(N * N * sizeof(double));
    double* C = (double*) malloc(N * N * sizeof(double));

    // Fill matrices A and B with random values between -100 and 100
    srand48(65537); //Seed with Fermat prime
    fill(A, N, 100);
    fill(B, N, 100);

    // Call matrix multiply function
    square_dgemm(N, A, B, C);

    // Compute and print Frobenius norm of C
    double norm, sqsum = 0.0;
    for(int i = 0; i < N * N; i++){
       sqsum += C[i] * C[i];
    }
    norm = sqrt(sqsum);

    printf("Frobenius norm of C = A B: %.2f\n", norm);

    // Cleanup
    free(A);
    free(B);
    free(C);
}
