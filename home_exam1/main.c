
#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf
#include <omp.h>
#include <time.h>

#include "functions/functions.h"

#include "read_graph_from_file1.c"
#include "read_graph_from_file2.c"
#include "count_mutual_links1.c"
#include "count_mutual_links2.c"
#include "top_n_webpages.c"



int main(int argc, char **argv) {

    clock_t start_all, end_all;
    double total_all;
    clock_t start, end;
    double total;
    /*
    int N1 = 0;
    char **table2D;
    read_graph_from_file1(argv[1], &N1, &table2D);


    int *num_involvements1;
    alloc1D(&num_involvements1, N1);


    start = clock();
    count_mutual_links1(N1, table2D, num_involvements1);
    end = clock();

    total = (double)(end - start)/CLOCKS_PER_SEC;
    printf("=========================================================\n" );
    printf("Time elapsed for count_mutual_links1: \t \t  %.6lf s     \n", total);
    printf("=========================================================\n");
    */

    int N2 = 0;
    int N_links = 0;




    int *row_ptr;
    int *col_idx;

    read_graph_from_file2(argv[1], &N2, &N_links, &row_ptr, &col_idx);

    int *num_involvements2;
    alloc1D(&num_involvements2, N2);

    start = clock();
    count_mutual_links2(N2-1, N_links, row_ptr, col_idx, num_involvements2);
    end = clock();

    total = (double)(end - start)/CLOCKS_PER_SEC;

    printf("=========================================================\n" );
    printf("Time elapsed for count_mutual_links2: \t \t  %.6lf s     \n", total);
    printf("=========================================================\n");

    start_all = clock();
    top_n_webpages(N2-1, num_involvements2, 10);
    end_all = clock();

    total_all = (double)(end_all - start_all)/CLOCKS_PER_SEC;
    printf("=========================================================\n" );
    printf("Time elapsed for top_n_webpages: \t \t  %.6lf s     \n", total_all);
    printf("=========================================================\n");

    return 0;
}
