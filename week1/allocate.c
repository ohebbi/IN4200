#include <stdio.h>
#include <stdlib.h>

int main(int narg, char ** args) {

  int *array;
  int n = atoi(args[1]);
  if (narg<2)
  {
    printf("ERROR: narg < 1\n");
    return EXIT_FAILURE;
  }
  array = (int*) malloc(n * sizeof(int));


  if(array == NULL)
  {
      printf("Error! memory not allocated.");
      exit(0);
  }

  /*
  Insert random values
  */
  for (int i = 0; i < n; i++)
  {
      array[i] = rand();

  }

  //double min, max = array[0];
  double min = array[0];
  double max = min;

  printf("n: %d \n", n);
  for (int i = 0; i < n; i++)
  {
    if (array[i]<min)
    {
      min = array[i];
      printf("hore %f \n", min);
    }
    if (max<array[i])
    {
      max = array[i];
    }
  }
  printf("min: %f \n", min);
  printf("max: %f \n", max);

  free(array);

  return 0;
}
