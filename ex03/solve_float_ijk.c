#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

double e_time(void) {
  static struct timeval now;
  gettimeofday(&now, NULL);
  return (double)(now.tv_sec  + now.tv_usec/1000000.0);
}

float *A, *B, *C;

# define MAT(p,j,i) p[(j)*N +(i)]

double rand_double() {
    return (double)rand()/((double)RAND_MAX + 1);
}

float rand_float()
{
    return (float)rand()/((float)RAND_MAX + 1); 
}

void mat_mul(float *x, float *y, float *z, int N) {
    int i, j, k;
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            for(k = 0; k < N; k++) {
                MAT(x,j,i) += MAT(y,j,k) * MAT(z,k,i);
            }
        }
    }
}

void mat_print(float *x, int N) {
    int i, j;
    for(j = 0; j < N; j++) {
        for(i = 0; i < N; i++) {
            printf("%f ", MAT(x,j,i));
        }
        printf("\n");
    }
}

int main(int argc,char *argv[]) {

    // get N
    if(argc != 2) {
      printf("Error: Please define n\n");
      return 1;
    }

    int N = atoi(argv[1]);

    if(N <= 0) {
        printf("Error: n is not a natural number\n");
        return 1;
    }

    // define matrix
    A = (float *)malloc(sizeof(float)*N*N);
    B = (float *)malloc(sizeof(float)*N*N);
    C = (float *)malloc(sizeof(float)*N*N);

    double st, en;

    // inject random numbers
    int i;
    for(i = 0; i < N*N; i++) {
        A[i] = 0.0;
        B[i] = rand_float();
        C[i] = rand_float();
    }

    /* if you want to check whether this programm is correct,
       uncomment below code
       
    printf("[B]\n");
    mat_print(B, N);

    printf("[C]\n");
    mat_print(C, N);
    */

    st = e_time();
    mat_mul(A, B, C, N);
    en = e_time();

    /*
    printf("[A]\n");
    mat_print(A, N);
    */

    printf("The Elapsed time is %.16f sec\n", en-st);

    free(A);
    free(B);
    free(C);
}