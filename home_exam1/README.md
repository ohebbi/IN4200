# Home exam 1

## How to compile this project
This project includes a Makefile and is compiled as follows. In bash, enter:

  - $ make

and then run the program by
  - $ ./main.exe <path/filename1> <path/filename2>

where filename1 is a web-graph that will be represented as a 2D-matrix. If this file is too big, it will result in a segmentation fault. Filename2 can be larger, and will be represented in a row-compressed storage.

To clean the build, write

 - $ make clean

## A successful run will look like this.
- $ ./main.exe data/100nodes.txt data/web-NotreDame.txt

Output:
Reading data graph: data/100nodes.txt ...
=========================================================
Time elapsed for count_mutual_links1: 	 	  0.051209 s     
=========================================================
Reading data graph: data/web-NotreDame.txt ...
/# of self-links: 27455
/# mutual links: 250329403
=========================================================
Time elapsed for count_mutual_links2: 	 	  0.005335 s     
=========================================================

data	index
===============
56653	7137
42023	260552
41871	236095
41868	260731
41868	260730
41868	260729
41868	260728
41868	260727
41868	260726
41868	260725
===============
=========================================================  
Time elapsed for top_n_webpages: 	 	  0.020446 s       
=========================================================  



## Dependencies
 - stdlib.h // rand, malloc and free.
 - stdio.h  // printf
 - omp.h    // parallelisation
 - time.h   // timing
