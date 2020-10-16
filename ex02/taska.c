#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc,char *argv[]) {
  int x, y, i, j;
  double sumsea;
  double **D = (double **)malloc(y * sizeof(double *));

  scanf("%d%d", &x, &y);

  /* input data (matrix)*/
  for(i = 0; i < y; i++) {
    D[i] = (double *)malloc(x * sizeof(double));
    for(j = 0; j < x; j++) {
      scanf("%lf,", &D[i][j]);
    }
  }

  /* x-direction */
  sumsea = 0;
  for(i = 0; i < y; i++) {
    for(j = 0; j < x; j++) {
      sumsea += D[i][j];
    //   printf("%lf ",D[i][j]);
    }
  }
  printf("x-direction sum: %lf\n", sumsea);

  /* y-direction */
  sumsea = 0;
  for(i = 0; i < x; i++) {
    for(j = 0; j < y; j++) {
      sumsea += D[j][i];
    //   printf("%lf ",D[j][i]);
    }
  }
  printf("y-direction sum: %lf\n", sumsea);

  return 0;
}
