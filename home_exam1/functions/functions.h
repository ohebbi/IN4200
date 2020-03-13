
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf



int alloc2D(char ***A, int n, int m){
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
int free2D(char ***A)
{
    free(*A[0]);
    free(*A);
    return 0;
}

// Print matrix values.
int printmat(char **A, int n, int m)
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
  for (size_t i = 0; i< (n); ++i){
    printf("%d ", A[i]);
  }
  printf("\n");
  return 0;
}
#endif
