#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf
#include <assert.h> // self-explanatory assert

// Description
// ----------
// Finds friends of ten of a MxN 2D-matrix by using
// MPI. This program is utililizing a row-wise
// decomposition, and all processors returns the same
// number of friends.
//
// Parameters
// ----------
// M: int
// N: initialized int
// v: initialized 2D-vector as int.
//
// Returns
// ----------
// total_friends_of_ten: int
//

int MPI_count_friends_of_ten(int M, int N, int** v){

    int numprocs, my_rank;
    // Get which rank every processor is, and how many processors in total
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    // Broadcast N and M to all nodes
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int *n_rows, *sendcounts, *Sdispls;

    // Calculate displacements and number of rows for each process.
    alloc1D(&n_rows, numprocs);

    // Used when scattering the matrix.
    alloc1D(&sendcounts, numprocs);
    alloc1D(&Sdispls, numprocs);

    int rows = M/numprocs;
    int remainder = M%numprocs;

    // Test that the number of processors is actually well-thought-about.
    assert(numprocs<=M && "Number of nodes >!  number of rows!!");

    // First rank has overlap only underneath.
    Sdispls[0] = 0;
    n_rows[0] = rows;
    sendcounts[0] = (n_rows[0] + 2)*N;

    // Only one node will require no overlap.
    if (numprocs<2){
        sendcounts[0] = n_rows[0]*N;
    }
    Sdispls[1]    = (n_rows[0] - 2)*N;


    // Last remainder processes gets an extra row.
    for (int rank = 1; rank < numprocs-1; rank++) {
        n_rows[rank] = rows;

        // If more rows remains, then we need to stack them up starting from
        // the bottom and up
        if (rank >= (numprocs - remainder)){
          n_rows[rank]++;
        }
        // 2 rows overlap over and under the rows for each node
        sendcounts[rank] = (n_rows[rank]+4)*N;
        Sdispls[rank+1] = Sdispls[rank] + n_rows[rank]*N;
    }

    // If more rows remains.
    n_rows[numprocs-1] = rows;
    if (numprocs-1 >= (numprocs - remainder)){
        n_rows[numprocs-1]++;
    }

    // In case number of nodes is 1, then this will become trouble without if loop.
    if (numprocs>1){
        sendcounts[numprocs-1]    = (n_rows[numprocs-1] + 2)*N;
    }

    // To stop at end value of matrix index [M,N]
    if (n_rows[numprocs-1]==1){
        sendcounts[numprocs-2] -= N;
    }

    // Diagnostics. Leave uncommented during bug-fixing.
    /*
    if (my_rank==0){
        for (int i = 0; i < numprocs; i++){
            printf("rank: %d, sendcounts: %d displacements: %d, num_rows = %d\n",i, sendcounts[i], Sdispls[i],n_rows[i]);
        }
    }
    */

    int *v_flat;
    if (my_rank == 0){
      alloc1D(&v_flat, M*N);
      //printmat(v,M,N);

      // Flatten the 2D matrix into an array.
      for (size_t i = 0; i < M; i++) {
          for (size_t j = 0; j < N; j++) {
              v_flat[idx(i,j,my_rank,N)] = v[i][j];
          }
      }
    }
    else {
      alloc1D(&v_flat, sendcounts[my_rank]); //malloc(M*n_rows[my_rank] * sizeof *v_flat);
    }



    //scatter v and send part of the flattened 2D matrix to the other nodes
    MPI_Scatterv(v_flat,                 // Sendbuff, matters only for root process.
                 sendcounts,
                 Sdispls,
                 MPI_INT,
                 v_flat,                 // Recieve buff is the same as sendbuf here.
                 sendcounts[my_rank],    // size of Recieve buff
                 MPI_INT,
                 0,
                 MPI_COMM_WORLD);

    int local_friends_of_ten = 0;

    for (int i = 0; i < n_rows[my_rank]; i++){
        for (int j = 0; j < N; j++){

            // down
            if ((idx(i+2,j,my_rank,N) < sendcounts[my_rank]) &&\
                 i+2 < M ){
                if (v_flat[idx(i  ,j,my_rank,N)]\
                  + v_flat[idx(i+1,j,my_rank,N)]\
                  + v_flat[idx(i+2,j,my_rank,N)] == 10) {

                    local_friends_of_ten++;
                }
            }

            // right
            if (j + 2 < N){
                if (v_flat[idx(i,j  ,my_rank,N)]\
                  + v_flat[idx(i,j+1,my_rank,N)]\
                  + v_flat[idx(i,j+2,my_rank,N)] == 10) {

                    local_friends_of_ten++;
                }
            }


            // right-down
            if ((idx(i+2,j,my_rank,N) < sendcounts[my_rank]) && (j + 2 < N)){
                if (v_flat[idx(i  ,j  ,my_rank,N)]\
                   +v_flat[idx(i+1,j+1,my_rank,N)]\
                   +v_flat[idx(i+2,j+2,my_rank,N)] == 10) {

                     local_friends_of_ten++;
                }
            }

            //right-up
            if ((idx(i-2,j,my_rank,N)+Sdispls[my_rank] >= 0) && j + 2 < N){ //for rank 1 if n_row[my_rank]==1.
                if (v_flat[idx(i  ,j  ,my_rank,N)]
                   +v_flat[idx(i-1,j+1,my_rank,N)]
                   +v_flat[idx(i-2,j+2,my_rank,N)] == 10) {

                    local_friends_of_ten++;
                }
            }
        }
    }

    int total_friends_of_ten;

    // Summing up all contributions and distributing to every processor.
    MPI_Allreduce(&local_friends_of_ten,
                  &total_friends_of_ten,
                  1,
                  MPI_INT,
                  MPI_SUM,
                  MPI_COMM_WORLD);


    // Free memory
    free(v_flat);
    free(sendcounts);
    free(Sdispls);
    free(n_rows);

    return total_friends_of_ten;
}
