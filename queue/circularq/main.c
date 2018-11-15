/**
 * @file main.h
 * @author Napat Rungruangbangchan
 * @date 18 October 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <stdlib.h>
#include "circularq.h"

#define QSIZEBYTE       60      // Note: Put data to Q have some overhead
#define TESTLOOPDAT		10		// Should error when put dat#10	

int main(){
	circularq_t ccq;
	int32_t dat;
	int32_t idx;

	if( circularq_create(&ccq, QSIZEBYTE) != CIRCULARQ_RET_OK){
		fprintf(stderr, "%s(%d)\n", __FUNCTION__, __LINE__);
		exit(-1);
	}

	/////////////////////////////////////////
	// Test: put q (not replace QData)
	printf("--------------------------------\n");
	
	// Put data
	for( idx=0; idx < TESTLOOPDAT; idx++){
		dat = 1000000+idx+1;
		if( circularq_putdata(&ccq, (uint8_t*)&dat, sizeof(dat)) == 0){
            fprintf(stderr, "Error %s(%d): %d\n", __FUNCTION__, __LINE__, dat);
            fflush(stderr);
        }else{
            fprintf(stdout, "%s(%d) put data: %d ok! qfreesize: %d\n", __FUNCTION__, __LINE__, dat, circularq_freesize(&ccq));
        }
	}
    
	// Get data 
	while(circularq_empty(&ccq) != true){
		if( circularq_getdata(&ccq, (uint8_t*)&dat) == 0){
			// q not emptry but can't get data then error
			fprintf(stderr, "Error %s(%d)\n", __FUNCTION__, __LINE__);
            fflush(stderr);
        }else{
			fprintf(stdout, "%s(%d) dat: %d\n", __FUNCTION__, __LINE__, dat);
		}
	}

    /////////////////////////////////////////
	// Test: put q (replace old QData if not space left)
	printf("--------------------------------\n");

	// Put data
	for( idx=0; idx < TESTLOOPDAT; idx++){
		dat = 1000000+idx+1;
		if( circularq_putdata_replace(&ccq, (uint8_t*)&dat, sizeof(dat)) <= 0){
			fprintf(stderr, "Error %s(%d)\n", __FUNCTION__, __LINE__);
		}
	}

	// Get data 
	while(circularq_empty(&ccq) != true){
		if( circularq_getdata(&ccq, (uint8_t*)&dat) <= 0){
			fprintf(stderr, "Error %s(%d)\n", __FUNCTION__, __LINE__);
		}else{
			fprintf(stdout, "%s(%d) dat: %d\n", __FUNCTION__, __LINE__, dat);
		}
	}

	/////////////////////////////////////////
	// END 
	printf("--------------------------------\n");
	circularq_destroy(&ccq);

	return 0; 
}
