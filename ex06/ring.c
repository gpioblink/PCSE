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

  int data = (id%2 == 0) ? 1 : 100;
  MPI_Status status;

  // 隣の番号を計算
  int previd = (id-1 >= 0) ? id - 1 : np - 1;
  int nextid = (id+1 < np) ? id + 1 : 0;


  MPI_Send(&data, 1, MPI_INT, previd, 0, MPI_COMM_WORLD);
  MPI_Send(&data, 1, MPI_INT, nextid, 0, MPI_COMM_WORLD);

  int a, b, c;
  MPI_Recv(&a, 1, MPI_INT, previd, 0, MPI_COMM_WORLD, &status);
  b = id;
  MPI_Recv(&c, 1, MPI_INT, nextid, 0, MPI_COMM_WORLD, &status);
  printf("I'm %d. Neighbor is %d and %d. Average is %lf\n", id, previd, nextid, (a+b+c)/3.0);

  MPI_Finalize();
  return 0;
}
