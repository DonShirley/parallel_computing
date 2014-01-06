/*
 ============================================================================
 Name        : ps_s_omp.c
 Author      : Adrian Kempf
 Version     :
 Copyright   : 
 Description :
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
		(void) fprintf(stderr,"Usage: prefix_sum_sequential -help | integer_count*\n");
		return EXIT_FAILURE;
	}

	int k, kk;
	int n = atoi(*(argv+1));
	int prefix_sums[n];
	double time1, time2;

	k = 0;
	kk = 0;

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

	time1 =  omp_get_wtime();

	for(k = 1; k < n; k = kk)
	{
		kk = k<<1;

		#pragma omp parallel for
		for(int i = kk-1; i < n; i+=kk)
		{
			prefix_sums[i] = prefix_sums[i-k] + prefix_sums[i];
		}
	}

	for(k = k>>1; k > 1; k = kk)
	{
		kk = k>>1;
		#pragma omp parallel for
		for(int i = k-1; i < (n-kk); i+=k)
		{
			prefix_sums[i+kk] = prefix_sums[i] + prefix_sums[i+kk];
		}
	}

	time2 = omp_get_wtime();

	(void) fprintf(stdout, "time: \t\t%f\n", (time2-time1));

//	for(int i = 0; i < n; i++)
//	{
//		(void) fprintf(stdout, "%i ", prefix_sums[i]);
//	}
//	(void) fprintf(stdout, "\n");
	return EXIT_SUCCESS;
}
