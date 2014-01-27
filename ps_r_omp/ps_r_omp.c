/*
 ============================================================================
 Name        : ps_r_omp.c
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

void ps(register int size, int n[])
 {
	 if(size < 2)
	 {
		 return;
	 }
	 int y[size/2];
	 
	 #pragma omp parallel for
	 for(int i = 0; i < size/2; i++)
	 {
		 y[i] = n[2*i] + n[2*i + 1];
	 }

	 ps(size/2, y);

	 n[1] = y[0];

	 #pragma omp parallel for
	 for(int i = 1; i < size/2; i++)
	 {
		 n[2*i] = y[i - 1] + n[2*i];
		 n[2*i + 1] = y[i];
	 }

	 if((size%2) == 1)
	 {
		 n[size - 1] = y[size/2 - 1] + n[size - 1];
	 }
 }

int main(int argc, char **argv)
{
	if((argc < 2) || (strcmp("-help", *(argv + 1)) == 0))
	{
		(void) fprintf(stderr,"Usage: prefix_sum_recursive -help | {integer }*\n");

		return EXIT_FAILURE;
	}

	int n = atoi(*(argv+1));
	int prefix_sums[n];
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

	time1 =  omp_get_wtime();

	ps(n, prefix_sums);

	time2 = omp_get_wtime();
	(void) fprintf(stdout, "time: \t\t%f\n", (time2-time1));

//	for(int i = 0; i < n; i++)
//	{
//		(void) fprintf(stdout, "%i ", prefix_sums[i]);
//	}
	return EXIT_SUCCESS;
}
