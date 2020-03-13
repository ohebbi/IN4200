#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf

#include "functions/functions.h"

int count_mutual_links1(int N, char **table2D, int *num_involvements){
  int tot_mutual_links = 0;
  int *mutual_links = 0;
  alloc1D(&mutual_links,N);


  for (int i = 0; i < N; i++){
      mutual_links[i] = 0;
      for (int j = 0; j < N; j++){
            mutual_links[i] += table2D[i][j];
      }
      if (mutual_links[i]<=1){
          mutual_links[i] = 0;
      }
      else{
          mutual_links[i] = (mutual_links[i]-1)*mutual_links[i]*0.5;
      }
      tot_mutual_links += mutual_links[i];
  }
  //Number of outbound involments
  for (int i = 0; i< N; i++){
      num_involvements[i] = 0; //assign values to the vector
      for (int j = 0; j < N; j++){
          if (table2D[j][i]){
              for (int k = 0; k<N; k++){
                  if (i!=k){
                      num_involvements[i] += table2D[j][k];
                  }
              }
          }
      }
  }
  //printvec(num_involvements,N);
  //printvec(mutual_links,N);
  //printf("%d\n", tot_mutual_links);

  return tot_mutual_links;
}



int count_mutual_links1_openMP(int N, char **table2D, int *num_involvements){
  int tot_mutual_links = 0;
  int *mutual_links = 0;
  alloc1D(&mutual_links,N);

  #pragma omp parallel for reduction(+:tot_mutual_links)
  for (int i = 0; i < N; i++){
      mutual_links[i] = 0;
      for (int j = 0; j < N; j++){
            mutual_links[i] += table2D[i][j];
      }
      //num_involvements[i]*=0.5*(num_involvements[i]+1);
      if (mutual_links[i]<=1){
          mutual_links[i] = 0;
      }
      else{
          mutual_links[i] = (mutual_links[i]-1)*mutual_links[i]*0.5;
      }
      tot_mutual_links += mutual_links[i];
  }
  //Number of outbound involments
  #pragma omp parallel for reduction(+:num_involvements[:N])
  for (int i = 0; i< N; i++){
      num_involvements[i] = 0; //assign values to the vector
      for (int j = 0; j < N; j++){
          if (table2D[j][i]){
              for (int k = 0; k<N; k++){
                  if (i!=k){
                      num_involvements[i] += table2D[j][k];
                  }
              }
          }
      }
  }
  //printvec(num_involvements,N);
  //printvec(mutual_links,N);
  //printf("%d\n", tot_mutual_links);

  return tot_mutual_links;
}
