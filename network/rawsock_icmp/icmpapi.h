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
int ping(char *dst_addr,char *src_addr,int timeout_ms);
//char* getip();		//BUG!!!
#endif
