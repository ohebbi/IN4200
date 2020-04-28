#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf

int MPI_count_friends_of_ten(int M, int N, int** v){
    int numprocs, my_rank;

    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);

    /*
    * This is for rows-wise decomposition
    */
    int *n_rows, *recievecounts, *sendcounts, *Sdispls;

    // Calculate displacements and number of rows for each process.
    alloc1D(&n_rows, numprocs);

    // Used when scattering the matrix.
    alloc1D(&recievecounts, numprocs);
    alloc1D(&sendcounts, numprocs);
    alloc1D(&Sdispls, numprocs);

    int rows = M/numprocs;
    int remainder = M%numprocs;

    // First rank
    Sdispls[0] = 0;
    n_rows[0] = rows;
    sendcounts[0] = (n_rows[0] + 2)*N;
    recievecounts[0] = (n_rows[0] + 2)*N;
    Sdispls[1]    = (n_rows[0] - 2)*N;

    // Last remainder processes gets an extra row.
    for (int rank = 1; rank < numprocs-1; rank++) {
        n_rows[rank] = rows;
        if (rank >= (numprocs - remainder)){
          n_rows[rank]++;
        }
        sendcounts[rank] = (n_rows[rank]+4)*N;
        recievecounts[rank] = (n_rows[rank]+4)*N;
        Sdispls[rank+1] = Sdispls[rank] + (n_rows[rank]-2)*N;

    }

    n_rows[numprocs-1] = rows;
    if (numprocs-1 >= (numprocs - remainder)){
      n_rows[numprocs-1]++;
    }

    sendcounts[numprocs-1]    = (n_rows[numprocs-1] + 2)*N;
    recievecounts[numprocs-1] = (n_rows[numprocs-1] + 2)*N; // why not 2?
    /*
    for (int i = 0; i < numprocs; i++){
        printf("sendcounts: %d Sdispls: %d\n", sendcounts[i], Sdispls[i]);
    }
    */
    printf("rank: %d, displacements:%d \n", my_rank, Sdispls[my_rank]);

    int *v_flat;
    if (my_rank == 0){
      alloc1D(&v_flat, M*N);
      printmat(v,M,N);
      // Initialize to some values:
      for (size_t i = 0; i < M; i++) {
          for (size_t j = 0; j < N; j++) {
              v_flat[idx(i,j,my_rank,N)] = v[i][j];
              //printf("%d ", v_flat[idx(i,j,my_rank,N)]);
          }
      }
      printf("\n");
    }
    else {

      alloc1D(&v_flat, recievecounts[my_rank]); //malloc(M*n_rows[my_rank] * sizeof *v_flat);
    }

    //scatter v and send part of the flattened 2D matrix to the other nodes
    MPI_Scatterv(v_flat,                 // Sendbuff, matters only for root process.
                 sendcounts,
                 Sdispls,
                 MPI_INT,
                 v_flat,                 // Recieve buff is the same as sendbuf here.
                 recievecounts[my_rank],
                 MPI_INT,
                 0,
                 MPI_COMM_WORLD);


    // ---------------------------------------------- // delete when done

    //printf("%d\n", n_rows[my_rank]);

    /*
    if (my_rank==0){
      for (int i = 0; i < sendcounts[0]; i++){
        printf("%d ", v_flat[i]);
      }
      printf("\n");
    }
    if (my_rank==1){
      for (int i = 0; i < sendcounts[1]; i++){
        printf("%d ", v_flat[i]);
      }
      printf("\n");
    }
    */
    // ---------------------------------------------- //
    int local_friends_of_ten = 0;

    for (int i = 0; i < n_rows[my_rank]; i++){
      //printf("%d\n", my_rank);
        for (int j = 0; j < N; j++){
            printf("rank: %d, i:%d, j:%d:, counts: %d, idx:(%d,%d,%d), value: %d and %d and %d", my_rank, i, j, sendcounts[my_rank], idx(i,j,my_rank,N),idx(i+1,j,my_rank,N),idx(i+2,j,my_rank,N), v_flat[idx(i,j,my_rank,N)], v_flat[idx(i+1,j,my_rank,N)], v_flat[idx(i+2,j,my_rank,N)]);

            if ((idx(i+2,j,my_rank,N) < sendcounts[my_rank]) && i+2 < M ){

                if (v_flat[idx(i,j,my_rank,N)] + v_flat[idx(i+1,j,my_rank,N)] + v_flat[idx(i+2,j,my_rank,N)] == 10) {

                    local_friends_of_ten++;
                    //printf("rank %d with nr friends: %d\n", my_rank, local_friends_of_ten);
                    printf(" downwards");
                    //printf("rank: %d, i:%d, j:%d:, counts: %d, idx:(%d,%d,%d), value: %d and %d and %d", my_rank, i, j, sendcounts[my_rank], idx(i,j,my_rank,N),idx(i+1,j+1,my_rank,N),idx(i+2,j+2,my_rank,N), v_flat[idx(i,j,my_rank,N)], v_flat[idx(i+1,j+1,my_rank,N)], v_flat[idx(i+2,j+2,my_rank,N)]);

                    //printf("myrank:%d, i=(%d,%d,%d), j=%d\n", my_rank, i,i+1,i+2, j);
                }
            }


            //correct one
            /*
            if (j + 2 < N && v_flat[idx(i,j,my_rank,N)] + v_flat[idx(i,j+1,my_rank,N)] + v_flat[idx(i,j+2,my_rank,N)] == 10) {
                local_friends_of_ten++;
                //printf("myrank:%d, %d, %d\n", my_rank, i, j);
                //printf(" right");
            }



            if ((2*my_rank*N + (i+2)*N + j < sendcounts[my_rank]) && j + 2 < N && v_flat[idx(i,j,my_rank,N)]+v_flat[idx(i+1,j+1,my_rank,N)]+v_flat[idx(i+2,j+2,my_rank,N)] == 10) {
                local_friends_of_ten++;
                //printf("myrank:%d, %d, %d\n", my_rank, i, j);
                //printf(" right-down");
            }


            if ((2*my_rank*N + (i-2)*N + j > 0) && j + 2 < N && v_flat[idx(i,j,my_rank,N)]+v_flat[idx(i-1,j+1,my_rank,N)]+v_flat[idx(i-2,j+2,my_rank,N)] == 10) {
                local_friends_of_ten++;
                //printf("myrank:%d, %d, %d\n", my_rank, i, j);
                //printf(" right-up");
                printf("rank:%d,  i=%d, j=%d\n",my_rank, i, j);


            }
            */
            printf("\n");
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
