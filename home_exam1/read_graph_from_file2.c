#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf

#include "functions/functions.h"

// Description
// ----------
// Opens a text file, allocates two vectors and
// reads the web graph in a compressed row storage format.
//
// Parameters
// ----------
// filename: char
// N, N_links: initialized ints
// row_ptr, col_idx: initialized vectors of ints

void read_graph_from_file2(char *filename, int *N, int *N_links, int **row_ptr, int **col_idx){

    FILE *file = fopen(filename, "r");

    //skipping lines
    fscanf(file, "%*[^\n]\n");
    fscanf(file, "%*[^\n]\n");

    //reading number of webpages and links.
    fscanf(file, "# Nodes: %d Edges: %d\n", &*N, &*N_links);
    fscanf(file, "%*[^\n]\n");

    (*N)++;   //row_ptr is of size N+1.
    int *fromNodeId; int *toNodeId;
    int fromNode; int toNode;

    alloc1D(col_idx, *N_links);

    alloc1D(row_ptr, *N);

    alloc1D(&fromNodeId,*N_links);
    alloc1D(&toNodeId,*N_links);

    fscanf(file,"%d %d", &fromNode, &toNode);
    int validcounts = 0;
    int totalcounts = 0;

    int total_number_read = 0;
    //read file and store every fromNode and toNode to each vector.
    while (!feof (file)){
        if (fromNode != toNode){
            fromNodeId[validcounts] = fromNode;
            toNodeId[validcounts] = toNode;
            validcounts++;
        }

        total_number_read += fscanf(file,"%d %d", &fromNode, &toNode);

        totalcounts++;
    }
    printf("# of self-links: %d\n", (totalcounts-validcounts));
    *N_links -= (totalcounts-validcounts);

    // The next for-loops shows how to make a CRS out of fromNodeId and toNodeId.
    // For detailed description, one can see the report. 
    for (int i = 0; i < *N_links; i++){
        (*row_ptr)[toNodeId[i]]++;
    }

    int sum = 0;
    for (int i = 0; i < *N; i++){
        int tmp       = (*row_ptr)[i];
        (*row_ptr)[i] = sum;
        sum          += tmp;
    }
    (*row_ptr)[*N] = *N_links;


    for (int i = 0; i < *N_links; i++){
        int row  = toNodeId[i];
        int dest = (*row_ptr)[row];
        (*col_idx)[dest] = fromNodeId[i];
        (*row_ptr)[row] ++;
    }

    int last = 0;
    for (int i = 0; i <= *N; i++){
        int tmp       = (*row_ptr)[i];
        (*row_ptr)[i] = last;
        last = tmp;
    }

    free(fromNodeId); free(toNodeId);
}
