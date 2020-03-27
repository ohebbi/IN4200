#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf

#include "functions/functions.h"

void top_n_webpages(int num_webpages, int *num_involvements, int n) {

  assert(n>1){
    printf("Error! Must show more than 1\n");
    exit(-1); // must include stdlib.h
  }
  int *index;
  alloc1D(&index,n);

  int *top_webpages;
  alloc1D(&top_webpages,n);

  #pragma omp parallel for ordered schedule(dynamic)
  for(int i=1; i < (n); i++){

      for (int j=0; j < (num_webpages); j++){
          if (num_involvements[j] > top_webpages[0]){
              top_webpages[0] = num_involvements[j];
              index[0]        = j;
          }

          else if (num_involvements[j] > top_webpages[i]){
              top_webpages[i] = num_involvements[j];
              index[i]        = j;

              // Check for earlier occurents with this index
              #pragma omp ordered
              for (int k = 0; k < i; k++){
                  if (index[k] == j){
                      top_webpages[i] = 0;
                      index[i]        = 0;
                  }
              }
          }
      }
  }

  printf("\ndata\tindex\n");
  printf("===============\n");
  for (int i = 0; i < n; i++){
      printf("%d\t%d\n", top_webpages[i], index[i]);
  }

  printf("===============\n");
  free(index);
  free(top_webpages);
}
