#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <time.h>

int printvec(char *A, int n){
  //printf("  ");
  for (size_t i = 0; i< (n); ++i){
    printf("%d ", A[i]);
  }
  printf("\n");
  return 0;
}

int inner(){
  int num_threads = 2;
  int N = 100000000;
  int i,j, sqrt_N;
  char *array = malloc(N); // N is a predefined very large integer
  array[0] = array[1] = 0;

  #pragma omp parallel for num_threads(num_threads)
  for (i=2; i<N; i++)
    array[i] = 1;

  sqrt_N = (int)(sqrt(N)); // square root of N

  for (i=2; i<=sqrt_N; i++) {
    if (array[i]) {
      #pragma omp parallel for num_threads(num_threads)
      for (j=i*i; j<N; j+=i)
        array[j] = 0;
    }
  }
  //printvec(array, N);
  free (array);
  return 0;
}

int outer(){
  int N = 100000000;
  int num_threads = 2;
  int i,j, sqrt_N;
  char *array = malloc(N); // N is a predefined very large integer
  array[0] = array[1] = 0;

  #pragma omp parallel for num_threads(num_threads)
  for (i=2; i<N; i++)
    array[i] = 1;

  sqrt_N = (int)(sqrt(N)); // square root of N
  #pragma omp parallel for num_threads(num_threads)
  for (i=2; i<=sqrt_N; i++) {
    if (array[i]) {
      for (j=i*i; j<N; j+=i)
        array[j] = 0;
    }
  }
  //printvec(array, N);

  free (array);
  return 0;
}

int uten(){
  int N = 100000000;
  int i,j, sqrt_N;
  char *array = malloc(N); // N is a predefined very large integer
  array[0] = array[1] = 0;

  for (i=2; i<N; i++)
    array[i] = 1;

  sqrt_N = (int)(sqrt(N)); // square root of N
  for (i=2; i<=sqrt_N; i++) {
    if (array[i]) {
      for (j=i*i; j<N; j+=i)
        array[j] = 0;
    }
  }
  //printvec(array, N);

  free (array);
  return 0;
}
int oppg2(){
  double start1, end1, start2, end2, start3, end3;
  double tot1, tot2, tot3;
  start1 = omp_get_wtime();
  inner();
  end1 = omp_get_wtime();

  start2 = omp_get_wtime();
  outer();
  end2 = omp_get_wtime();


  start3 = omp_get_wtime();
  uten();
  end3 = omp_get_wtime();


  tot1 = (double)(end1 - start1);
  tot2 = (double)(end2 - start2);
  tot3 = (double)(end3 - start3);

  printf("outer loop: %.10lf s\n", tot1);
  printf("inner loop: %.10lf s\n", tot2);
  printf("1234 loop:: %.10lf s\n", tot3);
  return 0;
}



int main(int argc, char const *argv[]) {
  oppg2();


  return 0;
}
