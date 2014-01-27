## MAKEFILE ##

CC = gcc
CFLAGS = -fopenmp -std=gnu99 -pedantic -Wall -g
OPT = -O0

all:ps_hs_omp

ps_s_r:ps_hs_omp
	$(CC) $(CFLAGS) -o ps_hs_omp $(OPT) ps_hs_omp.c

clean:
	rm -f *.o * ps_s_r


