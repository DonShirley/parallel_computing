/*
 ============================================================================
 Name        : ps_testbench.c
 Author      : Adrian Kempf
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv)
{
	if((argc < 5) || (strcmp("-help", *(argv + 1)) == 0))
	{
		(void) fprintf(stderr,"Usage: ps_testbench -help | executable test_iteration_count(int) max_int(int) int_count(count)\n");
		return EXIT_FAILURE;
	}

	int iteration_count = atoi(*(argv + 2));
	int max_int = atoi(*(argv + 3));
	int int_count = atoi(*(argv + 4));
	FILE* output_file;
	char* command = malloc(2 + strlen(*(argv+1)) + 1 + strlen(*(argv+4)) + 1);

	command = strcat(command, "./");
	command = strcat(command, *(argv+1));
	command = strcat(command, " ");
	command = strcat(command, *(argv+4));

	for(int j = 0; j < iteration_count; j++)
	{
		srandom((int)time(NULL));

		output_file = fopen("test","wb");
		for(int i = 0; i < int_count; i++)
		{
			(void) fprintf(output_file, "%i ", (int)(random()%max_int));
		}
		fclose(output_file);
//		system(command);
	}


	return EXIT_SUCCESS;
}
