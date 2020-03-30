# =====================================
# Title: 		MAKEFILE
# Date: 		10.03.2020
# Author: 	ohebbi
# =====================================



CC 			:= gcc
PROFILE := -pg

EXEC 		= main.exe
FLAGS		= -fopenmp -O3 
DEP 		= functions.h

SRC := $(wildcard *.c)

$(EXEC): $(SRC)
				$(CC) $(FLAGS) main.c -o $@

clean :
	@rm -f *.exe $(PROGRAMS)
test :
	$(CC) $(FLAGS) unit_tests/unit_test.c -o test.exe; ./test.exe
