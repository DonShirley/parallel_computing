/*
 ============================================================================
 Name        : ps_hs_omp.c
 Author      : Adrian Kempf
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

int main(int argc, char **argv)
{
	if((argc < 2) || (strcmp("-help", *(argv + 1)) == 0))
	{
		(void) fprintf(stderr,"Usage: ps_hs_omp -help | {integer }*\n");

		return EXIT_FAILURE;
	}

	int n = atoi(*(argv+1));
	int* prefix_sums = (int*)malloc(n*sizeof(int));
	double time1, time2;

	FILE* input_file = fopen ("test", "r");
	int j = 0;
	int m = 0;
	fscanf (input_file, "%i", &j);
	while (!feof (input_file))
	{
		if(m == n)
		{
			break;
		}
		prefix_sums[m] = j;
		fscanf (input_file, "%i", &j);
		m++;
	}
	fclose (input_file);

	(void) fprintf(stdout, "max_threads: \t%i\n", omp_get_max_threads());

	time1 = omp_get_wtime();
	
	int* prefix_sums_temp =(int*)malloc(n*sizeof(int));
	int* temp = NULL;
	for(int k = 1; k < n; k <<= 1)
	{
		for(int i = 0; i < k; i++)
		{
			prefix_sums_temp[i] = prefix_sums[i];
		}
		for(int i = k; i < n; i++)
		{
			prefix_sums_temp[i] = prefix_sums[i-k] + prefix_sums[i];
		}
		temp = prefix_sums;
		prefix_sums = prefix_sums_temp;
		prefix_sums_temp = temp;
	}
	prefix_sums = prefix_sums_temp;
	time2 = omp_get_wtime();
	(void) fprintf(stdout, "time: \t\t%f\n", (time2-time1));

	for(int i = 0; i < n; i++)
	{
		(void) fprintf(stdout, "%i ", prefix_sums[i]);
	}
	return EXIT_SUCCESS;
}
