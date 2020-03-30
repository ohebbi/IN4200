#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf

#include "functions/functions.h"

// Description
// ----------
// Finds the number of mutual links and number of outbound involvements
// given a 2D-table that has read a webgraph.
//
// Parameters
// ----------
//
// N: int
// table2D: 2D-vector as char with given values with shape NxN
// num_involvements: initialized 1D-vector of length N
//
// Returns
// ----------
// tot_mutual_links: 1D-array of length N
//
int count_mutual_links1(int N, char **table2D, int *num_involvements){
  int tot_mutual_links = 0;
  int *mutual_links = 0;
  alloc1D(&mutual_links,N);


  for (int i = 0; i < N; i++){
      mutual_links[i] = 0;
      for (int j = 0; j < N; j++){
            mutual_links[i] += table2D[i][j];
            //Number of outbound involvements
            if (table2D[j][i]){
                for (int k = 0; k<N; k++){
                    if (i!=k){
                        num_involvements[i] += table2D[j][k];
                    }
                }
            }
      }
      if (mutual_links[i]<=1){
          mutual_links[i] = 0;
      }
      else{
          mutual_links[i] = (mutual_links[i]-1)*mutual_links[i]*0.5;
      }
      tot_mutual_links += mutual_links[i];
  }
  return tot_mutual_links;
}



int count_mutual_links1_openMP(int N, char **table2D, int *num_involvements){
  int tot_mutual_links = 0;
  int *mutual_links = 0;
  alloc1D(&mutual_links,N);

  #pragma omp parallel for num_threads(2) reduction(+:tot_mutual_links, num_involvements[:N])
  for (int i = 0; i < N; i++){
      mutual_links[i] = 0;
      for (int j = 0; j < N; j++){
            mutual_links[i] += table2D[i][j];
            //Number of outbound involvements
            if (table2D[j][i]){
                for (int k = 0; k<N; k++){
                    if (i!=k){
                        num_involvements[i] += table2D[j][k];
                    }
                }
            }
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
  return tot_mutual_links;
}
