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

const char string_int[] = "1234";
const char string_float[] = "1706.1986";

void using_atox(){
	int 		num_int 	= atoi(string_int);
	long int 	num_long 	= atol(string_int);
	double 		num_double 	= atof(string_float);

	fprintf(stdout, "%s(%d) %d\n", __FUNCTION__, __LINE__, num_int);
	fprintf(stdout, "%s(%d) %ld\n", __FUNCTION__, __LINE__, num_long);
	fprintf(stdout, "%s(%d) %lf\n", __FUNCTION__, __LINE__, num_double);

	return;
}

void prefered_converter(){
	int 		num_int 	= (int)strtol(string_int, (char **)NULL, 10);
	long int 	num_long 	= strtol(string_int, (char **)NULL, 10);
	float 		num_float 	= strtof(string_float, (char **)NULL);
	double 		num_double 	= strtod(string_float, (char **)NULL);
	long double num_ldouble = strtold(string_float, (char **)NULL);

	fprintf(stdout, "%s(%d) %d \t size: %lu\n", __FUNCTION__, __LINE__, num_int, sizeof(num_int));
	fprintf(stdout, "%s(%d) %ld \t size: %lu\n", __FUNCTION__, __LINE__, num_long, sizeof(num_long));
	fprintf(stdout, "%s(%d) %f \t size: %lu\n", __FUNCTION__, __LINE__, num_float, sizeof(num_float));	
	fprintf(stdout, "%s(%d) %lf \t size: %lu\n", __FUNCTION__, __LINE__, num_double, sizeof(num_double));
	fprintf(stdout, "%s(%d) %Lf \t size: %lu\n", __FUNCTION__, __LINE__, num_ldouble, sizeof(num_ldouble));

	return;
}

int main(int argc, char * argv[]){

	// Stay away from atox function 
	// because when the value cannot be represented, handling of errors behavior is undefined.
	// https://stackoverflow.com/questions/7021725/converting-string-to-integer-c	
	using_atox();
	printf("----------------------\n");

	prefered_converter();
	printf("----------------------\n");

	return 0;
}
