#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf

#include "count_friends_of_ten.c"
#include "functions/functions.h"

int main(int argc, char const *argv[]) {
  /* code */
  int** v;
  int M, N;

  /*
  M = 5;
  N = 5;
  alloc2D(&v, M, N);
  assignvalues(v, M, N);
  */

  /*
  M = 10;
  N = 6;
  alloc2D(&v, M, N);
  assignvalues_big_matrix(v, M, N);
  */

  M = 20;
  N = 35;
  alloc2D(&v, M, N);
  assign_random_integers(v, M, N);

  int number_of_friends = count_friends_of_ten(M, N, v);
  printf("number of friends: %d\n", number_of_friends);
  printmat(v, M, N);
  return 0;
}
