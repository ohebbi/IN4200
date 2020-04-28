#include <mpi.h>
#include <stdio.h>

#include "functions/functions.h"
#include "mpi_count_friends_of_ten.c"
#include "count_friends_of_ten.c"
int main (int argc, char **argv) {

  int M=0, N=0, my_rank, num_triple_friends; int **v=NULL;
  MPI_Init (&argc, &argv);

  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

  if (my_rank==0) {
    // decide the values for M and N
    M = 10;
    N = 6;

    // allocate 2D array v and assign it with suitable values
    alloc2D(&v, M, N);
    //assignvalues(v, M, N);
    assignvalues_big_matrix(v, M, N);

  }
  num_triple_friends = MPI_count_friends_of_ten (M, N, v);
  printf("MPI rank <%d>: number of triple friends=%d\n", my_rank, num_triple_friends);
  if (my_rank==0){
    // deallocation of 2D array v
    free2D(&v);

  }
  MPI_Finalize();
  return 0;
}
