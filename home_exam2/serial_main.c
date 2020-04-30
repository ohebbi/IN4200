#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf

#include "count_friends_of_ten.c"
#include "functions/functions.h"

// Description
// ----------
// Main serialized program where one chooses the dimensions M and N
// of an MxN matrix, and finds the appropiate values of it.
// Writes out the number of triple friends of the matrix.
//

int main(int argc, char const *argv[]) {

  // Initialize v, M and N.
  int** v;
  int M, N;

  // decide the values for M and N
  M = 10000;
  N = 10000;

  // allocate 2D array v and assign it with suitable values
  alloc2D(&v, M, N);
  assign_random_integers(v, M, N);

  // call function to find number of friends.
  int num_triple_friends = count_friends_of_ten(M, N, v);

  printf("number of friends: %d\n", num_triple_friends);

  return 0;
}
