#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf
#include <assert.h> // self-explanatory assert
int MPI_count_friends_of_ten(int M, int N, int** v){
    int numprocs, my_rank;

    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("\nNumber of processors: %d\n\n", numprocs);
    /*
    * This is for rows-wise decomposition
    */
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
    //assert(rows>1 && "Increase dimension of matrix or decrease number of\
                nodes. Maybe serial-implementation is a better option.");

    // First rank has overlap only underneath.
    Sdispls[0] = 0;
    n_rows[0] = rows;
    sendcounts[0] = (n_rows[0] + 2)*N;

    // Only one node will require no overlap.
    if (numprocs<2){
        sendcounts[0] = n_rows[0]*N;
        //printf("rows=%d, numprocs=%d, tall 120 = %d, while sendcounts=%d ?\n",rows, numprocs, n_rows[0]*N,sendcounts[0]);
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



    // Given many nodes will result in very few rows for each node, this will
    // keep the program sane.
    /*
    if (n_rows[0]-2<=0){
      Sdispls[1]    = 0;
    }
    */

    // In case number of nodes is 1, then this will become trouble without if loop.
    if (numprocs>1){
        sendcounts[numprocs-1]    = (n_rows[numprocs-1] + 2)*N;
    }
    if (n_rows[1]==1) {
        sendcounts[1] -= N;
    }
    if (n_rows[numprocs-1]==1){
        sendcounts[numprocs-2] -= N;
    }

    if (my_rank==0){
        for (int i = 0; i < numprocs; i++){
            printf("rank: %d, sendcounts: %d displacements: %d, num_rows = %d\n",i, sendcounts[i], Sdispls[i],n_rows[i]);
        }
    }

    //printf("rank: %d, displacements:%d, num_rows = %d \n", my_rank, Sdispls[my_rank], n_rows[my_rank]);

    int *v_flat;
    if (my_rank == 0){
      alloc1D(&v_flat, M*N);
      printmat(v,M,N);
      // Initialize to some values:
      for (size_t i = 0; i < M; i++) {
          for (size_t j = 0; j < N; j++) {
              v_flat[idx(i,j,my_rank,N)] = v[i][j];
          }
      }
      printf("\n");
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
                 sendcounts[my_rank],
                 MPI_INT,
                 0,
                 MPI_COMM_WORLD);


    // ---------------------------------------------- // delete when done

    //printf("%d\n", n_rows[my_rank]);


    if (my_rank==1){
      printf("my_rank=%d\n", my_rank);
      for (int i = 0; i < sendcounts[1]; i++){
        printf("%d ", v_flat[i]);
      }
      printf("\n");
    }
    if (my_rank==2){
      printf("my_rank=%d\n", my_rank);
      for (int i = 0; i < sendcounts[2]; i++){
        printf("%d ", v_flat[i]);
      }
      printf("\n");
    }
    if (my_rank==3){
      printf("my_rank=%d\n", my_rank);
      for (int i = 0; i < sendcounts[3]; i++){
        printf("%d ", v_flat[i]);
      }
      printf("\n");
    }

    // ---------------------------------------------- //
    int local_friends_of_ten = 0;

    for (int i = 0; i < n_rows[my_rank]; i++){
      //printf("%d\n", my_rank);
        for (int j = 0; j < N; j++){
            //printf("rank: %d, i:%d, j:%d:, counts: %d, idx:(%d,%d,%d), value: %d and %d and %d", my_rank, i, j, sendcounts[my_rank], idx(i,j,my_rank,N),idx(i+1,j,my_rank,N),idx(i+2,j,my_rank,N), v_flat[idx(i,j,my_rank,N)], v_flat[idx(i+1,j,my_rank,N)], v_flat[idx(i+2,j,my_rank,N)]);

            if ((idx(i+2,j,my_rank,N) < sendcounts[my_rank]) &&\
                 i+2 < M ){

                if (v_flat[idx(i  ,j,my_rank,N)]\
                  + v_flat[idx(i+1,j,my_rank,N)]\
                  + v_flat[idx(i+2,j,my_rank,N)] == 10) {

                    local_friends_of_ten++;
                    //printf("rank: %d, i = %d, j = %d, value = %d+%d+%d, idx = (%d,%d,%d)\n", my_rank, i, j, v_flat[idx(i,j,my_rank,N)], v_flat[idx(i+1,j,my_rank,N)], v_flat[idx(i+2,j,my_rank,N)], idx(i,j,my_rank,N), idx(i+1,j,my_rank,N), idx(i+2,j,my_rank,N));
                    //printf(" downwards");
                    //printf("rank: %d, i:%d, j:%d:, counts: %d, idx:(%d,%d,%d), value: %d and %d and %d", my_rank, i, j, sendcounts[my_rank], idx(i,j,my_rank,N),idx(i+1,j+1,my_rank,N),idx(i+2,j+2,my_rank,N), v_flat[idx(i,j,my_rank,N)], v_flat[idx(i+1,j+1,my_rank,N)], v_flat[idx(i+2,j+2,my_rank,N)]);

                    //printf("myrank:%d, i=(%d,%d,%d), j=%d\n", my_rank, i,i+1,i+2, j);
                }
            }


            //correct one --- hooold that thought

            if (j + 2 < N){
                if (v_flat[idx(i,j  ,my_rank,N)]\
                  + v_flat[idx(i,j+1,my_rank,N)]\
                  + v_flat[idx(i,j+2,my_rank,N)] == 10) {
                    
                    local_friends_of_ten++;
                //printf("myrank:%d, %d, %d\n", my_rank, i, j);
                //printf(" right");
                }
            }

            /*

            if ((2*my_rank*N + (i+2)*N + j < sendcounts[my_rank]) &&\\
                j + 2 < N && v_flat[idx(i  ,j  ,my_rank,N)]\
                            +v_flat[idx(i+1,j+1,my_rank,N)]\
                            +v_flat[idx(i+2,j+2,my_rank,N)] == 10) {

                local_friends_of_ten++;
                //printf("myrank:%d, %d, %d\n", my_rank, i, j);
                //printf(" right-down");
            }


            if ((2*my_rank*N + (i-2)*N + j > 0) && j + 2 < N && v_flat[idx(i,j,my_rank,N)]+v_flat[idx(i-1,j+1,my_rank,N)]+v_flat[idx(i-2,j+2,my_rank,N)] == 10) {
                local_friends_of_ten++;
                //printf("myrank:%d, %d, %d\n", my_rank, i, j);
                //printf(" right-up");

                //printf("rank:%d,  i=%d, j=%d\n",my_rank, i, j);


            }
            */
            //printf("\n");
        }
    }

    int total_friends_of_ten;
    MPI_Allreduce(&local_friends_of_ten,
                  &total_friends_of_ten,
                  1,
                  MPI_INT,
                  MPI_SUM,
                  MPI_COMM_WORLD);


    return total_friends_of_ten;
}
