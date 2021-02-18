/**
 * Distributed memory (MPI) parallel computation of pi.
 * 
 * @author Akash Pallath
 */
#include<mpi.h>
#include<stdio.h>

long double pi(long long nsteps){
    
}

int main(int argc, char* argv[]){ 
    long long nsteps;
    if(argc < 2){
        printf("Required argument: number of steps to compute pi for\n");
        exit(-1);
    }
    nsteps = atoll(argv[1]);

    long double comp_pi = pi(nsteps);
    long double error = fabs(comp_pi - REFPI);
    printf("%lli steps; pi = %.25Lf; error = %.25Lf\n", nsteps, comp_pi, error);
}
