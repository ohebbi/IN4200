
#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf

#include "read_graph_from_files.h"









void read_graph_from_file1(char *filename, int *N, char ***table2D) {

  //open file
  FILE *file = fopen (filename, "r");
  char c[1000];
  int number;
  if (file == NULL || file == NULL){
    printf("Error! Could not open file\n");
    exit(-1); // must include stdlib.h
  }
  printf("jiiihaa\n" );

  //skipping lines
  fscanf(file, "%*[^\n]\n");
  fscanf(file, "%*[^\n]\n");
  // -- need number of nodes and edges here ---

  //skipping lines
  fscanf(file, "%*[^\n]\n");


  fscanf(file,"%c", &c);

  //while((ch = fgetc(file)) != EOF){
  //  printf(ch);
  //}
}




















int main(int argc, char const *argv[]) {

  int N = 0;
  char **table2D;
  alloc2D(&table2D,N,N);

  read_graph_from_file1("test_readfile.txt", &N, &table2D);




  free2D(table2D);

  return 0;
}
