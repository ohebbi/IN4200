#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf

#include "count_friends_of_ten.c"
#include "functions/functions.h"

int main(int argc, char const *argv[]) {
  /* code */
  int** v;
  int M = 10;
  int N = 6;
  alloc2D(&v, M, N);

  for (int i = 0; i < M; i++){
    for (int j = 0; j < N; j++){
      v[i][j] = 0;
    }
  }
  alloc2D(&v, M, N);
  //assignvalues(v, M, N);
  assignvalues_big_matrix(v, M, N);

  int number_of_friends = count_friends_of_ten(M, N, v);
  printf("number of friends: %d\n", number_of_friends);
  printmat(v, M, N);
  return 0;
}
