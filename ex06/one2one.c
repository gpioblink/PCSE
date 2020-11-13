#include <stdio.h>
#include "mpi.h"
int main(int argc, char *argv[] )
{
  int np, id;
  MPI_Init(&argc, &argv);

  // 起動されたプロセス数の取得
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  // 自分のidを取得
  MPI_Comm_rank(MPI_COMM_WORLD, &id);

  int data;
  MPI_Status status;

  if(id != 0) {
    data = id * id;
    MPI_Send(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  } else {
    int i;
    for(i=1; i<np; i++) {
      MPI_Recv(&data, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
      printf("receive %d from %d\n", data, i);
    }
  }

  MPI_Finalize();
  return 0;
}
