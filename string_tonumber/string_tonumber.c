/**
 * @file string_tonumber.c
 * @author Napat Rungruangbangchan
 * @date 20 July 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	char string_int[] = "1234";
	char string_float[] = "1706.1986";

	int num_int = atoi(string_int);
	long int num_long = atol(string_int);
	double num_float = atof(string_float);

	fprintf(stdout, "%d\n", num_int);
	fprintf(stdout, "%ld\n", num_long);
	fprintf(stdout, "%f\n", num_float);

	return 0;
}
