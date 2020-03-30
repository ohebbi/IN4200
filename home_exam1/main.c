
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

// Description:
// Test program.
//
// Parameters:
// filename1 and filename2. Reads .txt-files.
//

int main(int argc, char **argv) {

    clock_t start_all, end_all;
    double total_all;
    clock_t start1, end1, start2, end2, start3, end3, start4, end4;
    double total1, total2, total3, total4;

    int N1 = 0;
    char **table2D;
    printf("Reading data graph: %s ... \n", argv[1]);
    start1 = clock();
    read_graph_from_file1(argv[1], &N1, &table2D);
    end1 = clock();
    total1 = (double)(end1 - start1)/CLOCKS_PER_SEC;

    printf("=========================================================\n" );
    printf("Time elapsed for read_graph_from_file1: \t  %.6lf s     \n", total1);
    printf("=========================================================\n");

    int *num_involvements1;
    alloc1D(&num_involvements1, N1);


    start2 = clock();
    count_mutual_links1(N1, table2D, num_involvements1);
    end2 = clock();

    total2 = (double)(end2 - start2)/CLOCKS_PER_SEC;
    printf("=========================================================\n" );
    printf("Time elapsed for count_mutual_links1: \t \t  %.6lf s     \n", total2);
    printf("=========================================================\n");


    int N2 = 0;
    int N_links = 0;

    int *row_ptr;
    int *col_idx;
    printf("Reading data graph: %s ... \n", argv[2]);
    start3 = clock();
    read_graph_from_file2(argv[2], &N2, &N_links, &row_ptr, &col_idx);
    end3 = clock();
    total3 = (double)(end3 - start3)/CLOCKS_PER_SEC;
    printf("=========================================================\n" );
    printf("Time elapsed for read_graph_from_file2: \t  %.6lf s     \n", total3);
    printf("=========================================================\n");


    int *num_involvements2;
    alloc1D(&num_involvements2, N2);

    start4 = clock();
    count_mutual_links2(N2-1, N_links, row_ptr, col_idx, num_involvements2);
    end4 = clock();

    total4 = (double)(end4 - start4)/CLOCKS_PER_SEC;

    printf("=========================================================\n" );
    printf("Time elapsed for count_mutual_links2: \t \t  %.6lf s     \n", total4);
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
