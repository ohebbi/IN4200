
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf
#include <time.h> //

//#define idx(i,j) (2*my_rank*N + i*N + j)

int idx(int i, int j, int my_rank, int N){
  return (2*my_rank*N + i*N + j);
}

int alloc2D(int ***A, int n, int m){
    *A = malloc(n * sizeof *A);
    (*A)[0] = malloc(n*m * sizeof (*A)[0]);
    if (!(*A)[0] || !*A){
        // Allocation failed.
        printf("Allocation failed\n");
        return 1;
    }

    for (size_t i = 1; i < n; i++) {
        (*A)[i] = &((*A)[0][i*m]);
    }

    return 0;
}

int alloc1D(int **A, int n){
    *A = malloc(n * sizeof(int));

    return 0;
}

// Free pointers allocated in alloc2D.
int free2D(int ***A)
{
    free(*A[0]);
    free(*A);
    return 0;
}

// Print matrix values.
int printmat(int **A, int n, int m)
{
    printf("Matrix:\n");
    for (size_t i = 0; i < n; ++i){
        printf("| ");
        for (size_t j = 0; j < m; ++j){
            printf("%d ", A[i][j]);
        }
        printf("|\n");
    }
    return 0;
}

int printvec(int *A, int n){
  //printf("  ");
  for (size_t i = 0; i < n; ++i){
    printf("%d ", A[i]);
  }
  printf("\n");
  return 0;
}

int assignvalues(int** v, int M, int N){

  for (int i = 0; i < M; i++){
    for (int j = 0; j < N; j++){
      v[i][j] = 0;
    }
  }

  v[0][0] = 2; v[0][3] = 1;
  v[1][1] = 2; v[1][2] = 4; v[1][3] = 4;
  v[2][0] = 1; v[2][1] = 4; v[2][2] = 6; v[2][3] = 2; v[2][4] = 4;
  v[3][0] = 3; v[3][1] = 6; v[3][3] = 2; v[3][4] = 4;
  v[4][2] = 4; v[4][3] = 6;

  return 0;
}

int assignvalues_big_matrix(int** v, int M, int N){

  v[0][0] = 0; v[0][1] = 4; v[0][2] = 0; v[0][3] = 0; v[0][4] = 0; v[0][4] = 0;
  v[1][0] = 6; v[1][2] = 2; v[1][2] = 4; v[1][3] = 5; v[1][4] = 7; v[1][4] = 9;
  v[2][0] = 6; v[2][1] = 5; v[2][2] = 4; v[2][3] = 3; v[2][4] = 2; v[2][4] = 1;
  v[3][0] = 7; v[3][1] = 8; v[3][2] = 9; v[3][3] = 3; v[3][4] = 2; v[3][4] = 4;
  v[4][0] = 5; v[4][1] = 7; v[4][2] = 8; v[4][3] = 3; v[4][4] = 2; v[4][4] = 1;
  v[5][0] = 4; v[5][1] = 5; v[5][2] = 6; v[5][3] = 9; v[5][4] = 3; v[5][4] = 2;
  v[6][0] = 5; v[6][1] = 7; v[6][2] = 9; v[6][3] = 4; v[6][4] = 6; v[6][4] = 2;
  v[7][0] = 6; v[7][1] = 1; v[7][2] = 5; v[7][3] = 4; v[7][4] = 5; v[7][4] = 0;
  v[8][0] = 3; v[8][1] = 0; v[8][2] = 2; v[8][3] = 1; v[8][4] = 0; v[8][4] = 8;
  v[9][0] = 4; v[9][1] = 3; v[9][2] = 0; v[9][3] = 1; v[9][4] = 0; v[9][4] = 1;

  return 0;
}

int assign_random_integers(int** v, int M, int N){
  //srand(time(NULL));   // Initialization, should only be called once for randomn sequences. 
  for (int i = 0; i < M; i++){
      for (int j = 0; j < N; j++){
          v[i][j] = rand() % 10;
      }
  }
  return 0;
}
#endif
