

int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements){
  int *mutual_links;
  alloc1D(&mutual_links,(N-1)); //is of size one less than the size to row_ptr

  int tot_mutual_links = 0;

  for (int i = 0; i<(N-1); i++){
    num_involvements[i]=0;
    mutual_links[i] = row_ptr[i+1]-row_ptr[i];
    if (mutual_links[i]<=1){
        mutual_links[i] = 0;
    }
    else{
        mutual_links[i] = (mutual_links[i]-1)*mutual_links[i]*0.5;
    }
    tot_mutual_links += mutual_links[i];
  }
  //printvec(mutual_links,N-1);
  printf("# mutual links: %d\n", tot_mutual_links);

  for (int i = 0; i < (N); i++){
      if ((row_ptr[i+1] - row_ptr[i])>1){
          //printf("%d %d\n", i, (row_ptr[i+2] - row_ptr[i+1]));
          for (int j = row_ptr[i]; j < (row_ptr[i+1]); j++){
              //printf("%d\n", j);
              num_involvements[col_idx[j]] += (row_ptr[i+1] - (row_ptr[i]))-1;
          }
      }
  }
  //printvec(num_involvements,N);
  return tot_mutual_links;
}

int count_mutual_links2_openMP(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements){
  int *mutual_links;
  alloc1D(&mutual_links,(N-1)); //is of size one less than the size to row_ptr

  int tot_mutual_links = 0;

  //#pragma omp parallel for schedule(dynamic)
  for (int i = 0; i<(N-1); i++){
    num_involvements[i]=0;
    mutual_links[i] = row_ptr[i+1]-row_ptr[i];
    if (mutual_links[i]<=1){
        mutual_links[i] = 0;
    }
    else{
        mutual_links[i] = (mutual_links[i]-1)*mutual_links[i]*0.5;
    }
    tot_mutual_links += mutual_links[i];
  }
  //printvec(mutual_links,N-1);
  printf("# mutual links: %d\n", tot_mutual_links);

  #pragma omp parallel for schedule(dynamic)
  for (int i = 0; i < (N); i++){
      if ((row_ptr[i+1] - row_ptr[i])>1){
          //printf("%d %d\n", i, (row_ptr[i+2] - row_ptr[i+1]));
          for (int j = row_ptr[i]; j < (row_ptr[i+1]); j++){
              //printf("%d\n", j);
              num_involvements[col_idx[j]] += (row_ptr[i+1] - (row_ptr[i]))-1;
          }
      }
  }
  //printvec(num_involvements,N);
  return tot_mutual_links;
}
