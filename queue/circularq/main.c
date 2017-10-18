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

#define QSIZE_SUPPORT		10			// 1 guard band then support 9 buff
#define QTAIL_PADDING	((QSIZE_SUPPORT*2))

int main(){
	circularq_t ccq;
	int32_t dat;
	int32_t idx;

	if( circularq_create(&ccq, (sizeof(dat) * QSIZE_SUPPORT) + QTAIL_PADDING ) != 0){
		fprintf(stderr, "%s(%d)\n", __FUNCTION__, __LINE__);
		exit(-1);
	}

	/////////////////////////////////////////
	// Test: put q (not replace QData)
	printf("--------------------------------\n");
	
	// Put data
	for( idx=0; idx < QSIZE_SUPPORT; idx++){
		dat = 1000000+idx+1;
		if( circularq_putdata(&ccq, (uint8_t*)&dat, sizeof(dat)) <= 0){
			fprintf(stderr, "Error %s(%d)\n", __FUNCTION__, __LINE__);
		}
	}

	// Get data 
	while(circularq_empty(&ccq) != 1){
		if( circularq_getdata(&ccq, (uint8_t*)&dat) <= 0){
			fprintf(stderr, "Error %s(%d)\n", __FUNCTION__, __LINE__);
		}else{
			fprintf(stdout, "%s(%d) dat: %d\n", __FUNCTION__, __LINE__, dat);
		}
	}

	/////////////////////////////////////////
	// Test: put q (replace old QData if not space left)
	printf("--------------------------------\n");

	// Put data
	for( idx=0; idx < QSIZE_SUPPORT; idx++){
		dat = 1000000+idx+1;
		if( circularq_putdata_replace(&ccq, (uint8_t*)&dat, sizeof(dat)) <= 0){
			fprintf(stderr, "Error %s(%d)\n", __FUNCTION__, __LINE__);
		}
	}

	// Get data 
	while(circularq_empty(&ccq) != 1){
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
