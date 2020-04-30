# Home exam 2  

## How to compile this project
This project includes a Makefile and is compiled as follows.   

### Serial Code  
In bash, enter:  

  - $ make  

and then run the program by  
  - $ ./serial_main.exe

### Parallell code  
In bash, enter:  
- $ make mpi    

and then run the program by writing  
- $ mpirun -np x ./mpi_main.exe  

where x is the number of nodes one wants to run the program with.  

### Cleaning 
To clean the build, write

 - $ make clean

This will remove all '.exe' files.

## A successful run will look like this.
- $ make
- $ make clean



## Dependencies  
 - stdlib.h // rand, malloc and free.
 - stdio.h  // printf  
 - omp.h    // parallelisation  
 - time.h   // timing  
