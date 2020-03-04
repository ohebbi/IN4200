
#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf
#include "read_graph_from_files.h"


void read_graph_from_file1(char *filename, int *N, char ***table2D) {

    //open file
    FILE *file = fopen (filename, "r");

    int Edges;

    if (file == NULL || file == NULL){
      printf("Error! Could not open file\n");
      exit(-1); // must include stdlib.h
    }

    //skipping lines
    fscanf(file, "%*[^\n]\n");
    fscanf(file, "%*[^\n]\n");

    fscanf(file, "# Nodes: %d Edges: %d\n", &*N, &Edges);

    fscanf(file, "%*[^\n]\n");

    alloc2D(table2D, *N, *N);
    printmat(*table2D,N,N);

    int fromNode; int toNode;

    fscanf(file, "%d %d", &fromNode, &toNode);

    while (!feof (file))
    {
        printf("%d %d\n", fromNode, toNode);
        (*table2D)[toNode][fromNode]++;
        printmat(*table2D,N,N);
        fscanf(file,"%d %d", &fromNode, &toNode);
    }

    //printmat(*table2D,N,N);
    free2D(table2D);

}


void read_graph_from_file2(char *filename, int *N, int *N_links, int **row_ptr, int **col_idx){

    FILE *file = fopen(filename, "r");

    //skipping lines
    fscanf(file, "%*[^\n]\n");
    fscanf(file, "%*[^\n]\n");

    //reading number of webpages and links.
    fscanf(file, "# Nodes: %d Edges: %d\n", &*N, &*N_links);
    fscanf(file, "%*[^\n]\n");

    (*N)++;   //row_ptr is of size N+1.
    alloc1D(col_idx, *N_links);
    alloc1D(row_ptr, *N);

    //printvec(col_idx,N_links);

    int fromNode; int toNode;

    int **fromNodeId;
    int **toNodeId;

    alloc1D(fromNodeId,*N_links);
    alloc1D(toNodeId,*N_links);

    fscanf(file,"%d %d", &fromNode, &toNode);
    int i = 0;
    while (!feof (file)){
        //printf("%d %d\n", fromNode, toNode);

        fscanf(file,"%d %d", &fromNode, &toNode);

        (*fromNodeId)[i] = fromNode;
        (*toNodeId)[i] = toNode;

        i++;
    }
    printvec(toNodeId,N_links);

}




/////////////////////////////////////////////////////////////////////77
//REMEMBER TO FREE MEMORY!!!!
int main(int argc, char const *argv[]) {

    char **table2D;
    int N = 0;
    //read_graph_from_file1("test_readfile.txt", &N, &table2D);

    read_graph_from_file1("test_readfile2.txt", &N, &table2D);


    printf("CRS:\n\n");
    int N_links = 0;
    int *row_ptr;
    int *col_idx;
    read_graph_from_file2("test_readfile2.txt", &N, &N_links, &row_ptr, &col_idx);

    //read_graph_from_file2("test_readfile.txt", &N, &N_links, &row_ptr, &col_idx);

    return 0;
}
