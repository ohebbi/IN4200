#include <stdio.h>

int main(int argc, char const *argv[]) {
  double start = -0.5*0.5;
  double half = -0.5*0.5;
  double summation = 1;

  for (int i=0;i<=10;i++){
    summation = summation + half;
    half = half*start;
  }
  printf("%f \n", summation);
  return 0;
}
