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

#define IP_SRC			"192.168.10.85"
#define IP_DST1 		"192.168.10.81"	
#define IP_DST2 		"8.8.4.4"		// Google dns
#define IP_DST3 		"8.8.1.1"		// Should timeout error
#define PING_TIMEOUT 	(1000)

int main(void){
	int ret;	
    ret = ping(IP_SRC, IP_DST1, 50, PING_TIMEOUT);
    printf("dst: %s, ret = %d ms.\n", IP_DST1, ret);

    ret = ping(IP_SRC, IP_DST2, 50, PING_TIMEOUT);
    printf("dst: %s, ret = %d ms.\n", IP_DST2, ret);

    ret = ping(IP_SRC, IP_DST3, 50, PING_TIMEOUT);
    printf("dst: %s, ret = %d ms.\n", IP_DST3, ret);
	return 0;
}
