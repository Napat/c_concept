/**
 * @file qsort_example.c
 * @author Napat Rungruangbangchan
 * @date 19 July 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_int(const void *a, const void *b){
	return *(int *)a - *(int *)b;
}

int compare_char(const void *a, const void *b){
	return *(char *)a - *(char *)b;
}

int main(int argc, char * argv[]){
	int idx;
	
	int numint[] = {8 ,4, 7, 9, 5, 6, 2, 1, 3, 0};
	char txtarr[] = "qwertyuiopasdfghjklzxcvbnm";

	int numint_len = sizeof(numint)/sizeof(numint[0]);
	int txtarr_len = strlen(txtarr);

	// numint
	qsort(numint, numint_len, sizeof(numint[0]), compare_int);

	for(idx = 0; idx < numint_len; idx++){
		fprintf(stdout, "%d", numint[idx]);
	}
	fprintf(stdout, "\n");

	// txtarr
	qsort(txtarr, txtarr_len, sizeof(txtarr[0]), compare_char);

	fprintf(stdout, "%s", txtarr);
	fprintf(stdout, "\n");


	return 0;
}
