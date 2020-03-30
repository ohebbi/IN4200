#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf
#include <omp.h>

#include "functions/functions.h"

// Description
// ----------
// Finds the number of mutual links and number of outbound involvements
// given two 1D-vectors in the format of compressed row storage.
//
// Parameters
// ----------
//
// N, N_links: int
// row_ptr, col_idx: 1D-vector with length N, N_links, corresponding to a 2D-
//                   table in a compressed row storage format.
// num_involvements: initialized 1D-vector of length N
//
// Returns
// ----------
// tot_mutual_links: 1D-array of length N
//

int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements){
  int *mutual_links;
  alloc1D(&mutual_links,(N-1)); //is of size one less than the size to row_ptr

  int tot_mutual_links = 0;

  for (int i = 0; i<(N-1); i++){
    num_involvements[i]=0;
    mutual_links[i] = row_ptr[i+1]-row_ptr[i];
    if (mutual_links[i]<=1){
        mutual_links[i] = 0;
    }
    else{
        mutual_links[i] = (mutual_links[i]-1)*mutual_links[i]*0.5;
    }
    tot_mutual_links += mutual_links[i];
  }
  //printvec(mutual_links,N-1);
  printf("# mutual links: %d\n", tot_mutual_links);

  for (int i = 0; i < (N); i++){
      if ((row_ptr[i+1] - row_ptr[i])>1){
          for (int j = row_ptr[i]; j < (row_ptr[i+1]); j++){
              num_involvements[col_idx[j]] += (row_ptr[i+1] - (row_ptr[i]))-1;
          }
      }
  }
  return tot_mutual_links;
}

int count_mutual_links2_openMP(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements){
  int *mutual_links;
  alloc1D(&mutual_links,(N-1)); //is of size one less than the size to row_ptr

  int tot_mutual_links = 0;

  #pragma omp parallel for num_threads(1) reduction(+:tot_mutual_links)
  for (int i = 0; i<(N-1); i++){
    num_involvements[i]=0;
    mutual_links[i] = row_ptr[i+1]-row_ptr[i];
    if (mutual_links[i]<=1){
        mutual_links[i] = 0;
    }
    else{
        mutual_links[i] = (mutual_links[i]-1)*mutual_links[i]*0.5;
    }
    tot_mutual_links += mutual_links[i];
  }
  //printvec(mutual_links,N-1);
  printf("# mutual links: %d\n", tot_mutual_links);

  #pragma omp parallel for reduction(+:num_involvements[:N]) num_threads(1)
  for (int i = 0; i < (N); i++){
      if ((row_ptr[i+1] - row_ptr[i])>1){
          for (int j = row_ptr[i]; j < (row_ptr[i+1]); j++){
              num_involvements[col_idx[j]] += (row_ptr[i+1] - (row_ptr[i]))-1;
          }
      }
  }
  //printvec(num_involvements,N);
  return tot_mutual_links;
}
