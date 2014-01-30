## MAKEFILE ##

CC = gcc
CFLAGS = -fopenmp -std=gnu99 -pedantic -Wall -g
OPT = -O0

all:ps_s_s

ps_s_s:ps_s
	$(CC) $(CFLAGS) -o ps_s $(OPT) ps_s.c

clean:
	rm -f *.o * ps_s


