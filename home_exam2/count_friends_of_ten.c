#include <stdlib.h> // rand, malloc and free.
#include <stdio.h>  // printf

int count_friends_of_ten(int M, int N, int** v){
    int friends_of_ten = 0;
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){

            if (i + 2 < M && v[i][j] + v[i+1][j] + v[i+2][j] == 10) {
                friends_of_ten++;
                printf("%d, %d\n", i, j);
            }

            /*
            if (j + 2 < N && v[i][j] + v[i][j+1] + v[i][j+2] == 10) {
                friends_of_ten++;
                //printf("%d, %d\n", i, j);

            }


            if (i + 2 < M && j + 2 < N && v[i][j]+v[i+1][j+1]+v[i+2][j+2] == 10) {
                friends_of_ten++;
                //printf("%d, %d\n", i, j);

            }



            if (i - 2 >= 0 && j + 2 < N && v[i][j]+v[i-1][j+1]+v[i-2][j+2] == 10) {
                friends_of_ten++;
                //printf("%d, %d\n", i, j);

            }
            */

        }
    }
  return friends_of_ten;
}
