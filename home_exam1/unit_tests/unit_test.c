
#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf

#include <omp.h>
#include <time.h>
#include "../functions/functions.h"

#include "../read_graph_from_file1.c"
#include "../read_graph_from_file2.c"
#include "../count_mutual_links1.c"
#include "../count_mutual_links2.c"
#include "../top_n_webpages.c"

char **correct_matrix(){
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

int check_2Dtable(char **test_matrix, int N) {
    char **correct_table;
    correct_table = correct_matrix();
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (correct_table[i][j] != test_matrix[i][j]){
                printf("2D matrix is not correct - check out read_graph_from_file1!\n");
                return 1;
            }
        }
    }

    return 0;
}
int check_1Dvector(int *test_vector, int *correct_vector, int N){
    for (int i = 0; i < N; i++){
        if (test_vector[i] != correct_vector[i]){
          printf("1D vector is not correct!\n");
          printvec(test_vector, N);
          printvec(correct_vector, N);
          return 1;
        }
    }
    return 0;
}

int *correct_involvements(int N){
    int *involvments;
    alloc1D(&involvments, N);
    for (int i = 0; i < N; i++){
        involvments[i]=0;
    }
    involvments[0] = 2; involvments[2] = 4; involvments[3] = 6;
    involvments[4] = 5; involvments[5] = 2; involvments[6] = 4;
    involvments[7] = 3;
    return involvments;
}
int *row_vector(int N){
    int *row;
    alloc1D(&row, N);
    for (int i = 0; i < N; i++){
        row[i] = 0;
    }
    row[1] = 1; row[2] = 4; row[3] = 5; row[4] = 6;
    row[5] = 9; row[6]= 12; row[7]= 14; row[8] = 17;
    return row;
}
int *column_vector(int N){
  int *column;
  alloc1D(&column, N);
  for (int i = 0; i < N; i++){
      column[i] = 0;
  }
  column[0] = 6; column[2] = 2; column[3] = 3; column[5] = 1;
  column[6] = 2; column[7] = 3; column[8] = 6; column[9] = 3;
  column[10] = 4; column[11] = 7; column[12] = 4; column[13] = 7;
  column[14] = 4; column[15] = 5; column[16] = 6;
  return column;
}
// This is a testing program that checks if the read..-files and the
// count..-files have been properly implemented.
//
// It checks up against test_readfile.txt
//
int unit_test() {

  int N1 = 0;
  int check1; int check2; int check3; int check4; int check5;
  int check6; int check7;

  char **table2D;
  read_graph_from_file1("data/test_readfile.txt", &N1, &table2D);
  check1 = check_2Dtable(table2D, N1);
  if (check1 == 1){
      return 1;
  }


  int *correct_vector;
  int test_mutual_links1;
  int *num_involvements1;
  alloc1D(&num_involvements1, N1);

  test_mutual_links1 = count_mutual_links1(N1, table2D, num_involvements1);
  correct_vector = correct_involvements(N1);
  check2 = check_1Dvector(num_involvements1, correct_vector, N1);

  if (check2 == 1 || (test_mutual_links1 != 13)){
      return 1;
  }





  int N2 = 0;
  int N_links = 0;

  int *row_ptr;
  int *col_idx;
  int *correct_col;
  int *correct_row;

  read_graph_from_file2("data/test_readfile.txt", &N2, &N_links, &row_ptr, &col_idx);

  correct_col = column_vector(N_links);
  correct_row = row_vector(N2);
  check4 = check_1Dvector(row_ptr, correct_row, N2);
  check5 = check_1Dvector(col_idx, correct_col, N_links);

  if (check4 == 1 || (check5 == 1)){
      printf("read_graph_from_file2 is NOT correct\n");
      return 1;
  }


  int *num_involvements3;
  alloc1D(&num_involvements3, N2);
  int test_mutual_links3;
  clock_t start, end;
  double total;

  start = clock();
  test_mutual_links3 = count_mutual_links2(N2, N_links, row_ptr, col_idx, num_involvements3);
  end = clock();

  check6 = check_1Dvector(num_involvements3, correct_vector, N2-1);
  if (check6 == 1 || (test_mutual_links3 != 13)){
    printf("%d\n", test_mutual_links3);
      printf("count_mutual_links2 is NOT correct\n");
      return 1;
  }


  int *num_involvements4;
  alloc1D(&num_involvements4, N2);
  int test_mutual_links4;

  total = (double)(end - start)/CLOCKS_PER_SEC;


  printf("=========================================================\n" );
  printf("Time elapsed for count_mutual_links2: \t \t  %.6lf s     \n", total);
  printf("=========================================================\n");
  printf("==          All tests have been successful             ==\n");
  printf("=========================================================\n");

  free2D(&table2D);
  return 0;
}
int main(int argc, char const *argv[]) {
  int check_unit_tests;
  check_unit_tests = unit_test();
  if (check_unit_tests == 1){
    printf("Unit tests did not pass\n");
    return 1;
  }
  return 0;
}
