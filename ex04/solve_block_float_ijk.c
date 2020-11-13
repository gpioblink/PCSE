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

void mat_mul(float *x, float *y, float *z, int si, int sj, int sk, int b, int N) {
    int i, j, k;
    for(i = si*b; i < si*b+b; i++) {
        for(j = sj*b; j < sj*b+b; j++) {
            for(k = sk*b; k < sk*b+b; k++) {
                MAT(x,i,j) += MAT(y,i,k) * MAT(z,k,j);
            }
        }
    }
}

void mat_mma(float *x, float *y, float *z, int NB, int b, int N) {
    int i, j, k;
    for(i = 0; i < NB; i++) {
        for(j = 0; j < NB; j++) {
            for(k = 0; k < NB; k++) {
                mat_mul(x, y, z, i, j, k, b, N); // {read block A(I,K) B(K,J) into fast memory}
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

    // get NB and b
    if(argc != 3) {
      printf("Error: Please define N and b\n");
      return 1;
    }

    int NB = atoi(argv[1]);
    int b = atoi(argv[2]);

    if(NB <= 0) {
        printf("Error: n is not a natural number\n");
        return 1;
    }

    if(b <= 0) {
        printf("Error: b is not a natural number\n");
        return 1;
    }

    int N = NB*b;

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
    */ 
    printf("[B]\n");
    mat_print(B, N);

    printf("[C]\n");
    mat_print(C, N);
    

    st = e_time();
    mat_mma(A, B, C, NB, b, N);
    en = e_time();


    printf("[A]\n");
    mat_print(A, N);


    printf("The Elapsed time is %.16f sec\n", en-st);

    free(A);
    free(B);
    free(C);
}