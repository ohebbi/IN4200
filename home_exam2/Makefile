# =====================================
# Title: 		MAKEFILE
# Date: 		21.04.2020
# Author: 	ohebbi
# =====================================



CC 			:= gcc
PROFILE := -pg

EXEC 		= serial_main.exe
FLAGS		= -O3
DEP 		= functions/functions.h

SRC := $(wildcard *.c)

$(EXEC): $(SRC)
				$(CC) $(FLAGS) serial_main.c -o $@
mpi :
	mpicc -Wall mpi_main.c -o mpi_main.exe
clean :
	@rm -f *.exe $(PROGRAMS)
