#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double a) {
  return (4.0 / (1.0 + a*a));
}

int main(int argc,char *argv[]) {
  int n, id, np, i;
  double PI25DT = 3.141592653589793238462643;
  double startwtime, endwtime;
  double h, sum, x, mypi, realsum;
  int idxs, idxe;

  if (argc == 1) n = 1000;
  else n = atoi(argv[1])*1000;

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);

  MPI_Status status;

  if(id == 0) {
    h = 1.0/(double)n;
    for(i=1; i<np; i++) {
      idxs = (n/np)*i;
      idxe = (n/np)*(i+1) + (i-1 == np ? n % np : 0);
      MPI_Send(&h, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
      MPI_Send(&idxs, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
      MPI_Send(&idxe, 1, MPI_INT, i, 2, MPI_COMM_WORLD);  
    }
    realsum = 0.0;
    for(i=1; i<np; i++) {
      MPI_Recv(&sum, 1, MPI_DOUBLE, i, 3, MPI_COMM_WORLD, &status);
      realsum += sum;
    }
    mypi = h*realsum;
    printf("pi is approximately %.16f, Error is %.16f\n", mypi, fabs(mypi - PI25DT)/PI25DT);
  } else {
    sum = 0.0;
    MPI_Send(&h, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
    MPI_Send(&idxs, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
    MPI_Send(&idxe, 1, MPI_INT, i, 2, MPI_COMM_WORLD);
    startwtime = MPI_Wtime();
    for (i = idxs; i < idxe; i++) {
      x = h*((double)i - 0.5);
      sum += f(x);
    }
    endwtime = MPI_Wtime();
    MPI_Send(&sum, 1, MPI_DOUBLE, 0, 3, MPI_COMM_WORLD);
    printf("process %d finished for %ld sec\n", id, endwtime - startwtime);
  }
  MPI_Finalize();
  return 0;
}
