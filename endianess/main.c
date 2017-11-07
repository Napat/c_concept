/**
 * @file main.c
 * @author Napat Rungruangbangchan
 * @date 7 November 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include "endianchecker.h"

int main(){
	printf("This machine is %s endian\n", (is_bigendian()==true)?"BIG":"LITTLE");
	return 0;
} 
