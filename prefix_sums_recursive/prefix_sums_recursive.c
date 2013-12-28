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

//int argcounter;
//
//void prefix_sums(register int sum, char **argv)
//{
//	static int counter = 0;
//
//	counter++;
//	sum += atoi(*(argv + 1));
//
//	(void) fprintf(stdout, "%i ", sum);
//	if(counter == argcounter-1)
//	{
//		return;
//	}
//	prefix_sums(sum, (argv + 1));
//}

//void prefix_sums(register int size, char **argv)


 void prefix_sums(register int size, int n[])
 {
	 if(size < 2)
	 {
		 return;
	 }
	 int y[size/2];
	 for(int i = 0; i < size/2; i++)
	 {
		 y[i] = n[2*i] + n[2*i + 1];
	 }

	 prefix_sums(size/2, y);

	 n[1] = y[0];
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
//	argcounter = argc;
	//Following could be used for more than one run in one single program execution
	//int input[argc - 1];

//	prefix_sums(0, argv);

	int n[argc - 1];
//	int y[argc - 1];
	for(int i = 0; i < (argc - 1); i++)
	{
		n[i] = atoi(*(argv + i + 1));
	}

	prefix_sums((argc - 1), n);

	for(int i = 0; i < (argc - 1); i++)
	{
		(void) fprintf(stdout, "%i ", n[i]);
	}
	return EXIT_SUCCESS;
}
