## MAKEFILE ##

CC = gcc
CFLAGS = -fopenmp -std=gnu99 -pedantic -Wall -g -lm
OPT = -O0

all: ps_hs_b_omp.o
	$(CC) -o ps_hs_b_omp ps_hs_b_omp.c $(OPT) $(CFLAGS)

clean:
	rm -f *.o * ps_hs_b_omp

