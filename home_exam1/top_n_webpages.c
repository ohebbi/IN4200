#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf

#include "functions/functions.h"
int *array;

int compare_func (const void * a, const void * b) {
    int ia = *(int *)a;
    int ib = *(int *)b;

    return array[ia] < array[ib] ? -1 : array[ia] > array[ib];
}

void top_n_webpages(int num_webpages, int *num_involvements, int n) {

  int *index;
  alloc1D(&index,num_webpages);

  for(int i=0;i<(num_webpages);i++){
      index[i]=i;
  }
  array = num_involvements;
  qsort(index, num_webpages, sizeof(*index), compare_func);
  printf("\ndata\tindex\n");
  printf("===============\n");
  #pragma omp parallel for
  for (int i = num_webpages - 1; i > num_webpages - 1 - n; i--){
      printf("%d\t%d\n", num_involvements[index[i]], index[i]);
  }
  printf("===============\n");
}
