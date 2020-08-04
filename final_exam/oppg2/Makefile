# =====================================
# Title: 		MAKEFILE
# Date: 		10.03.2020
# Author: 	ohebbi
# =====================================



CC 			:= gcc-9
PROFILE := -pg

EXEC 		= main.exe
FLAGS		= -I/usr/local/opt/llvm/include -fopenmp -O3
# DEP 		= functions.h

CPPFLAGS = -I/usr/local/opt/llvm/include -fopenmp
LDFLAGS = -L/usr/local/opt/llvm/lib

SRC := $(wildcard *.c)

$(EXEC): $(SRC)
				$(CC) $(FLAGS) main.c -o $@

clean :
	@rm -f *.exe $(PROGRAMS)
test :
	$(CC) $(FLAGS) unit_tests/unit_test.c -o test.exe; ./test.exe
