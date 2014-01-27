## MAKEFILE ##

CC = gcc
CFLAGS = -fopenmp -std=gnu99 -pedantic -Wall -g
OPT = -O0

all:ps_r

ps_s_r:ps_r
	$(CC) $(CFLAGS) -o ps_r $(OPT) ps_r.c

clean:
	rm -f *.o * ps_s_r


