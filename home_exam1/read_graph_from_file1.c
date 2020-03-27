#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf

#include "functions/functions.h"

// Opens a text file, allocates a 2D-vector and
// reads the web graph into the table
//
// Parameters
// ----------
// filename: char
// N: initialized int
// table2D: initialized 2D-vector as char.
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
    //printmat(*table2D,N,N);

    int fromNode; int toNode;

    fscanf(file, "%d %d", &fromNode, &toNode);

    int total_number_read = 0;

    while (!feof (file))
    {
        if (fromNode != toNode){
            //printf("%d %d\n", fromNode, toNode);
            (*table2D)[toNode][fromNode]++;
            //printmat(*table2D,*N,*N);
        }
        total_number_read = fscanf(file,"%d %d", &fromNode, &toNode);
    }

    //printmat(*table2D,*N,*N);
    //free2D(table2D);

}
