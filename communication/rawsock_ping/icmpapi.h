/**
 * @file icmpapi.h
 * @author Napat Rungruangbangchan
 * @date 29 January 2011 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#ifndef PING_INC_GUARD
#define PING_INC_GUARD
int ping(char *src_addr, char *dst_addr, int payloadlen, int timeout_ms);
int ping_dos(char *src_addr, char *dst_addr, int payloadlen, int pkt_num);
//char* getip();		// not implement yet! : use to get source ip address
#endif
