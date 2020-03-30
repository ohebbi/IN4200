
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


/////////////////////////////////////////////////////////////////////77
//REMEMBER TO FREE MEMORY!!!!
int main(int argc, char const *argv[]) {

    clock_t start_all, end_all;
    double total_all;

    int N1 = 0;
    char **table2D;
    read_graph_from_file1("data/100nodes.txt", &N1, &table2D);


    int *num_involvements1;
    alloc1D(&num_involvements1, N1);

    int *num_involvements2;
    alloc1D(&num_involvements2, N1);

    clock_t start, end, start_MP, end_MP;
    double total, total_MP;

    start = clock();
    count_mutual_links1(N1, table2D, num_involvements1);
    end = clock();

    start_MP = clock();
    count_mutual_links1(N1, table2D, num_involvements2);
    end_MP = clock();

    total = (double)(end - start)/CLOCKS_PER_SEC;
    total_MP = (double)(end_MP - start_MP)/CLOCKS_PER_SEC;
    printf("=========================================================\n" );
    printf("Time elapsed for count_mutual_links1: \t \t  %.6lf s     \n", total);
    printf("Time elapsed for count_mutual_links1_openMP: \t  %.6lf s\n", total_MP);
    printf("Parallelisation: without / with Parallelisation = %f\n", total/total_MP);
    printf("=========================================================\n");


    int N2 = 0;
    int N_links = 0;

    int *row_ptr;
    int *col_idx;

    read_graph_from_file2("data/100nodes.txt", &N2, &N_links, &row_ptr, &col_idx);

    int *num_involvements3;
    alloc1D(&num_involvements3, N2-1);

    int *num_involvements4;
    alloc1D(&num_involvements4, N2-1);

    start = clock();
    count_mutual_links2(N2-1, N_links, row_ptr, col_idx, num_involvements3);
    end = clock();

    start_MP = clock();
    count_mutual_links2_openMP(N2-1, N_links, row_ptr, col_idx, num_involvements4);
    end_MP = clock();

    total = (double)(end - start)/CLOCKS_PER_SEC;
    total_MP = (double)(end_MP - start_MP)/CLOCKS_PER_SEC;

    printf("=========================================================\n" );
    printf("Time elapsed for count_mutual_links2: \t \t  %.6lf s     \n", total);
    printf("Time elapsed for count_mutual_links2_openMP: \t  %.6lf s\n", total_MP);
    printf("Parallelisation: without / with Parallelisation = %f\n", total/total_MP);
    printf("=========================================================\n");
    start_all = clock();

    top_n_webpages(N2-1, num_involvements4, 10);

    end_all = clock();

    total_all = (double)(end_all - start_all)/CLOCKS_PER_SEC;
    printf("\n: %.6lf \n", total_all);
    return 0;
}
