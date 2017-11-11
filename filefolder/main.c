/**
 * @file main.c
 * @author Napat Rungruangbangchan
 * @date 7 November 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <string.h>
#include "filefolder.h"

int main(){
	char buf[1024];
	int lscount;
	int lsorder;
	int buf_idx;

	printf("----------------\n");
	lsdir(".");

	printf("----------------\n");
	memset(buf, 0, sizeof(*buf));
	lscount 	= 0;
	buf_idx 	= 0;

	lsdir_buf(".", buf, &lscount);	
	for(lsorder = 0; lsorder < lscount; lsorder++){
		buf_idx += printf("%s", &(buf[buf_idx])) + 1;
	}

	return 0;
} 
