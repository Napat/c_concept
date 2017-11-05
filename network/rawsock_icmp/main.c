/**
 * @file main.h
 * @author Napat Rungruangbangchan
 * @date 5 November 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include "icmpapi.h"

#define IP_SRC			"192.168.43.230"
#define IP_DST1 		"8.8.8.8"		// Google dns
#define IP_DST2 		"8.8.4.4"		// Google dns
#define IP_DST3 		"8.8.1.1"		// Should timeout error
#define PING_TIMEOUT 	(1000)

int main(void){
	int ret;
	ret = ping(IP_DST1, IP_SRC, PING_TIMEOUT);
	printf("ret = %d\n", ret);
	return 0;
}
