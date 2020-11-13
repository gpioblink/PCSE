#include <stdio.h>
#include "mpi.h"
int main(int argc, char *argv[] )
{
  int np, id;
  MPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);

  int data = 3;
  MPI_Send(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

  MPI_Status status:
  int data;
  MPI_Recv(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
  printf("receive %d from %d\n", data, 1);

  printf("Hello world from process %d (%d)\n", id, np);
  MPI_Finalize();
  return 0;
}
