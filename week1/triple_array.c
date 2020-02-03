#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

  double ***A;

  int nx = 10;
  int ny = 10;
  int nz = 10;

  A = (double ***)    malloc(nx    *sizeof(double **));
  A[0] = (double **)  malloc(nx*ny  *sizeof(double *));
  A[0][0] = (double *)malloc(nx*ny*nz*sizeof(double ));

  //creating the matrix
  for (int i = 1; i<ny; i++)
  {
    A[i] = &(A[0][ny*i]);
  }

  for (int j=1; j<nz*ny; j++)
  {
    A[0][j] = &(A[0][0][nz]);
  }



  for (int i = 0; i<nx; i++)
  {
    for (int j = 0; j<ny; j++)
    {
      for (int k = 0; k<nz; k++)
      {
        A[i][j][k] = i*ny*nz + j*nz + k;
        printf("%f ",A[i][j][k]);
      }
      printf("\n");
    }
    printf("\n");
  }

  free(A[0][0]);
  free(A[0]);
  free(A);

  return 0;
}
