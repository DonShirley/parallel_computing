/*
 ============================================================================
 Name        : prefix_sums_recursive.c
 Author      : Adrian Kempf
 Version     :
 Copyright   :
 Description : Prefix-sums sequential recursive implementation
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int argcounter;

void prefix_sums(int sum, char **argv)
{
	static int counter = 0;

	counter++;
	sum += atoi(*(argv + 1));

	(void) fprintf(stdout, "%i ", sum);
	if(counter == argcounter-1)
	{
		return;
	}
	prefix_sums(sum, (argv + 1));
}

int main(int argc, char **argv)
{
	if((argc < 2) || (strcmp("-help", *(argv + 1)) == 0))
	{
		(void) fprintf(stderr,"Usage: prefix_sum_recursive -help | {integer }*\n");

		return EXIT_FAILURE;
	}
	argcounter = argc;
	//Following could be used for more than one run in one single program execution
	//int input[argc - 1];
	//Is a register version even possible?
	//register int prefix_sums[argc - 1];

	prefix_sums(0, argv);

	return EXIT_SUCCESS;
}
