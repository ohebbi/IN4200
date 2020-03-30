#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf

#include "functions/functions.h"


// Description
// ----------
// Will find the top n values in an 1D-array and print them out in a
// nice format.
//
// Parameters
// ----------
// num_webpages: int
// num_involvements: 1D-vector of length N
// n: int


void top_n_webpages(int num_webpages, int *num_involvements, int n) {

  int *top_indices;
  alloc1D(&top_indices,n);

  int *top_webpages;
  alloc1D(&top_webpages,n);

  int tmp_webpage;
  int tmp_index;

  #pragma omp parallel for ordered schedule(dynamic)
  for(int i=0; i < (n); i++){

      // Make sure to assign zero value.
      top_webpages[i] = 0;
      top_indices[i]=0;

      #pragma omp ordered
      for (int j=0; j < (num_webpages); j++){
          if (num_involvements[j] >= top_webpages[i]){

              // Assign temporary value in case it has been already counted.
              tmp_webpage = top_webpages[i];
              tmp_index = top_indices[i];

              // Assign new top-value
              top_webpages[i] = num_involvements[j];
              top_indices[i]  = j;

              // Check for earlier occurents with this index
              for (int k = 0; k < i; k++){
                  if (top_indices[k] == j){

                      // Assign last value
                      top_webpages[i] = tmp_webpage;
                      top_indices[i]  = tmp_index;
                  }
              }
          }
      }
  }

  // nice printing format.
  printf("\nwebpage\tindex\n");
  printf("===============\n");
  for (int i = 0; i < n; i++){
      printf("%d\t%d\n", top_webpages[i], top_indices[i]);
  }
  printf("===============\n");
  free(top_indices);
  free(top_webpages);
}
