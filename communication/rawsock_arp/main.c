/**
 * @file main.h
 * @author Napat Rungruangbangchan
 * @date 27 September 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include "arp_api.h"

#define INTERFACE_NAME 	("eth0")
unsigned char arpreq_target_ip[4] = {192, 168, 10, 81};	// who has arpreq_target_ip
unsigned char arpreq_source_ip[4] = {192, 168, 10, 86};	// tell arpreq_source_ip

int main(){
	arp_request(INTERFACE_NAME, arpreq_target_ip, arpreq_source_ip);
	arp_reply(INTERFACE_NAME, arpreq_source_ip);
	arp_reply(INTERFACE_NAME, arpreq_source_ip);
	arp_reply(INTERFACE_NAME, arpreq_source_ip);
	return 0; 
}
