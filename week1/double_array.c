#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char const *argv[]) {
  /* code */

  double **A;
  int n = 1000;
  int m = 1000;

  clock_t start, timer_rowwise, timer_colwise;

  /*
  //really do not need this test here.
  if (argc<2)
  {
    printf("ERROR: narg < 1\n");
    return EXIT_FAILURE;
  }
  */

  //m*n matrix
  A = (double **) malloc(n * sizeof(double *));
  A[0] = (double *) malloc(m* n * sizeof(double *));


  //creating the matrix

  for (int i = 1; i<n ; i++)
  {
    A[i] = &(A[i-1][n]);
  }

  start = clock();
  //test one
  for (int i = 0; i<m; i++)
  {
    for (int j = 0; j<n; j++)
    {
      A[i][j] = m*i+j;
    }
  }
  timer_rowwise = clock() - start;

  printf("test1: %f\n", (A[1][3]));
  printf("clock: %lu \n", timer_rowwise);


  //test two
  start = clock();

  for (int j = 0; j<n; j++)
  {
    for (int i = 0; i<m; i++)
    {
      A[i][j] = m*i+j;
    }
  }
  timer_colwise = clock() - start;

  printf("test1: %f\n", (A[1][3]));
  printf("clock: %lu \n", timer_colwise);

  free(A[0]);
  free(A);
  return 0;
}
