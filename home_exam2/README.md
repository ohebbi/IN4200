# Home exam 2  

## How to compile this project
This project includes a Makefile and is compiled as follows.   

### Serial Code  
In bash, enter:  

  - $ make  

and then run the program by writing   
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

## A successful run can look like this.
- $ make mpi   
mpicc -Wall mpi_main.c -o mpi_main.exe  
- $ mpirun -np 8 ./mpi_main.exe  
MPI rank <6>: number of triple friends=25185851  
MPI rank <4>: number of triple friends=25185851  
MPI rank <1>: number of triple friends=25185851  
MPI rank <5>: number of triple friends=25185851  
MPI rank <2>: number of triple friends=25185851  
MPI rank <7>: number of triple friends=25185851  
MPI rank <3>: number of triple friends=25185851  
MPI rank <0>: number of triple friends=25185851  

## Dependencies  
 - stdlib.h // rand, malloc and free.
 - stdio.h  // printf  
 - assert.h // test of program
  
