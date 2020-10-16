#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cmp_asc( const void *p, const void *q ) {
    if( *(double*)p > *(double*)q ) return 1;
    if( *(double*)p < *(double*)q ) return -1;
    return 0;
}

int cmp_desc( const void *p, const void *q ) {
    if( *(double*)p > *(double*)q ) return -1;
    if( *(double*)p < *(double*)q ) return 1;
    return 0;
}

int main(int argc,char *argv[]) {
  int x, y, n, i, j;
  double sumsea;

  scanf("%d%d", &x, &y);
  n = x * y;

  double *D = (double *)malloc(n * sizeof(double));

  /* input data*/
  for(i = 0; i < n; i++) {
    scanf("%lf,", &D[i]);
  }

  /* sort: ascending order */
  qsort(D, n, sizeof(double), cmp_asc);
  sumsea = 0;
  for(i = 0; i < n; i++) {
    sumsea += D[i];
    // printf("%lf,", D[i]);
  }
  printf("\nascending order sum: %lf\n", sumsea);

  /* sort: descending order */
  qsort(D, n, sizeof(double), cmp_desc);
  sumsea = 0;
  for(i = 0; i < n; i++) {
    sumsea += D[i];
    // printf("%lf,", D[i]);
  }
  printf("\ndescending order sum: %lf\n", sumsea);

  return 0;
}

