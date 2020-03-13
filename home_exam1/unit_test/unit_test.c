
#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf

#include <omp.h>
#include <time.h>
#include "../functions.h"
int **correct_matrix(){
  char **matrix;
  int N = 8;
  alloc2D(&matrix, N, N);
  for (int i = 0; i < N; i++){
      for (int j = 0; j < N; j++){
          matrix[i][j] = 0;
      }
  }
  matrix[0][6]=1;
  matrix[1][0]=1; matrix[1][2]=1; matrix[1][3]=1;
  matrix[2][0]=1;
  matrix[3][1]=1;
  matrix[4][2]=1; matrix[4][3]=1; matrix[4][6]=1;
  matrix[5][3]=1; matrix[5][4]=1; matrix[5][7]=1;
  matrix[6][4]=1; matrix[6][7]=1;
  matrix[7][4]=1; matrix[7][5]=1; matrix[7][6]=1;
  return matrix;
}

void check_2Dtable(char **matrix) {
  char **table;
  table = correct_matrix();

}

int unit_test(int argc, char const *argv[]) {

  int N1 = 0;


  char **table2D;
  read_graph_from_file1("../data/test_readfile.txt", &N1, &table2D);



  int *num_involvements1;
  alloc1D(&num_involvements1, N1);

  count_mutual_links1(N1, table2D, num_involvements1);


  printf("CRS:\n");
  int *num_involvements2;
  int N2 = 0;
  int N_links = 0;

  int *row_ptr;
  int *col_idx;

  read_graph_from_file2("../data/web-NotreDame.txt", &N2, &N_links, &row_ptr, &col_idx);

  alloc1D(&num_involvements2, N2);

  //int *num_involvements;
  clock_t start, end, start_MP, end_MP;
  double total, total_MP;

  start = clock();
  count_mutual_links2(N2, N_links, row_ptr, col_idx, num_involvements2);
  end = clock();

  start_MP = clock();
  count_mutual_links2_openMP(N2, N_links, row_ptr, col_idx, num_involvements2);
  end_MP = clock();

  total = (double)(end - start)/CLOCKS_PER_SEC;

  total_MP = (double)(end_MP - start_MP)/CLOCKS_PER_SEC;

  printf("Time elapsed for count_mutual_links2: %.6lf s\n", total);
  printf("Time elapsed for count_mutual_links2_openMP: %.6lf s\n", total_MP);
  printf("Parallelisation: without / with Parallelisation = %f\n", total/total_MP);

  top_n_webpages(N2, num_involvements2, 5);
  return 0;
}
