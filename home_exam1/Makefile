# =====================================
# Title: 		MAKEFILE
# Date: 		10.03.2020
# Author: 	ohebbi
# =====================================



CC 			:= gcc
PROFILE := -pg

EXEC 		= main.exe
FLAGS		= -Wall -fopenmp
DEP 		= functions.h

SRC := $(wildcard *.c)

$(EXEC): $(SRC)
				$(CC) $(FLAGS) main.c -o $@

clean :
	@rm -f *.exe $(PROGRAMS)
print-%  : ; @echo $* = $($*)
