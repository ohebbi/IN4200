# Home exam 1

## How to compile this project
This project includes a Makefile and is compiled as follows. In bash, enter:

  - $> make

and then run the program by
  - $> ./main.exe <path/filename1> <path/filename2>

where filename1 is a web-graph that will be represented as a 2D-matrix. If this file is too big, it will result in a segmentation fault. Filename2 can be larger, and will be represented in a row-compressed storage.

To clean the build, write

 - $> make clean

## Dependencies
 - stdlib.h // rand, malloc and free.
 - stdio.h  // printf
 - omp.h    // parallelisation
 - time.h   // timing
