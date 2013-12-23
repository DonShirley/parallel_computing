/*
 ============================================================================
 Name        : prefix_sums_sequential.c
 Author      : Adrian Kempf
 Version     :
 Copyright   :
 Description : Prefix-sums sequential non recursive implementation
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	if((argc < 2) || (strcmp("-help", *(argv + 1)) == 0))
	{
		(void) fprintf(stderr,"Usage: prefix_sum_sequential -help | {integer }*\n");
		return EXIT_FAILURE;
	}

	//Following could be used for more than one run in one single program execution
	//int input[argc - 1];

	//Is a register version even possible?
	//register int prefix_sums[argc - 1];

	int prefix_sums[argc - 1];

	for(int i = 1; i < argc; i++)
	{
		if(i != 1)
		{
			prefix_sums[i] = (atoi(*(argv + i)) + prefix_sums[i - 1]);
		}
		else
		{
			prefix_sums[i] = atoi(*(argv + i));
		}
		(void) fprintf(stdout, "%i ", prefix_sums[i]);
	}

	return EXIT_SUCCESS;
}
