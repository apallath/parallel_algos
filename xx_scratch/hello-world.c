#include <stdio.h> //defines BUFSIZ
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
   int rank, size, length;
   char name[MPI_MAX_PROCESSOR_NAME];

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Get_processor_name(name, &length);

   printf("%s: Hello world from process %d of %d\n", name, rank, size);

   MPI_Finalize();
}
