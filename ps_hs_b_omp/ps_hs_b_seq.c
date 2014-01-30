/*
 ============================================================================
 Name        : ps_hs_b_omp.c
 Author      : Adrian Kempf
 Version     :
 Copyright   : 
 Description : Prefix-sums with blocked Hillis-Steele algorithm.
 		Did not expect all processors to be free --> block number
		could be below 40.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <math.h>

int main(int argc, char **argv)
{
	if((argc < 2) || (strcmp("-help", *(argv + 1)) == 0))
	{
		(void) fprintf(stderr,"Usage: ps_hs_omp -help | {integer }*\n");

		return EXIT_FAILURE;
	}


	int n = atoi(*(argv+1));
	int* prefix_sums = (int*)malloc(n*sizeof(int));
	int* prefix_sums_work = (int*)malloc(n*sizeof(int));
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
		prefix_sums_work[m] = j;
		fscanf (input_file, "%i", &j);
		m++;
	}
	fclose (input_file);

	(void) fprintf(stdout, "max_threads: \t%i\n", omp_get_max_threads());
	

	time1 = omp_get_wtime();

	fprintf(stdout, "%d | %d | %d |\n", n, omp_get_max_threads(), n/omp_get_max_threads());	
	int as = (int) ceil(((double)n/(double)omp_get_max_threads()));
		
	int* b_array = NULL; 
	fprintf(stdout, "%d\n", as);		
//	#pragma omp parallel for	
	for(int b = 0; b < n; b += as)
	{
		int* temp = NULL;
		int length = 0;
		int* prefix_sums_temp = NULL;
		if((b + as) > n) // BUG? XXX
		{
			length = (n-b);
			prefix_sums_temp = (int*)malloc((n-b)*sizeof(int));
			fprintf(stdout, "last%d\n", b);	
		}
		else
		{
			length = as;
			fprintf(stdout, "%d|%d\n", b, as);	
			prefix_sums_temp = (int*)malloc(as*sizeof(int));
		}
		
		int* partial_ps_sums = (prefix_sums + b);	
		
		int k_counter = 0;
		for(int k = 1; k < length; k <<= 1)
		{
			k_counter++;
//			#pragma omp parallel for //try with and without this
			for(int i = 0; i < k; i++)
			{
				prefix_sums_temp[i] = partial_ps_sums[i];
			}
//			#pragma omp parallel for //try with and without this
			for(int i = k; i < length; i++)
			{
				prefix_sums_temp[i] = partial_ps_sums[i-k] + partial_ps_sums[i];
			}
			temp = partial_ps_sums;
			partial_ps_sums = prefix_sums_temp;
			prefix_sums_temp = temp;
			
			if(((k_counter % 2) == 1) && ((k<<1) >= length))
			{
				//not optimal, better with pointer array
				//could also be parallized --> communication !!??
				for(int i = 0; i < length; i++)
				{
					prefix_sums_temp[i] = partial_ps_sums[i];
				}
			}	
							
			for(int i = 0; i < length; i++)
			{
				(void) fprintf(stdout, "%i ", partial_ps_sums[i]);
			}	
			fprintf(stdout, "\n");
		}
//		free(prefix_sums_temp);
	}
	//just by one single processor	
	int size = 0;
	for(int b = as; b < n; b += as)
	{
		size++;
		b_array = realloc(b_array, size*sizeof(int));
		if(size == 1)
		{
			b_array[size-1] = prefix_sums[b-1];
		}
		else
		{
			b_array[size-1] = prefix_sums[b-1] + b_array[size-2];	
		}
	}
	int add = 0;
	/* Calculate final prefix sums as combination of single blocks */
	//parallized TODO
	for(int b = as; b < n; b += as)
	{
		int length = 0;
		if((b + as) > n) // BUG? XXX
		{
			length = (n-b);
		}
		else
		{
			length = as;
		}
	
		for(int i = 0; i < length; i++)
		{
			prefix_sums[b+i] += b_array[add];	
		}	
		add++;
	}

	time2 = omp_get_wtime();
	(void) fprintf(stdout, "time: \t\t%f\n", (time2-time1));

	for(int i = 0; i < n; i++)
	{
		(void) fprintf(stdout, "%i ", prefix_sums[i]);
	}
	(void) fprintf(stdout,"\n");

	return EXIT_SUCCESS;
}
