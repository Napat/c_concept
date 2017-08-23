/**
 * @file rtcaccess.h
 * @author Napat Rungruangbangchan
 * @date 14 Aguent 2017 
 * @brief This file is part of char driver sample
 * @Compiler: 
 * @License: 
 */

#ifndef __RTCACCESS_H__
#define __RTCACCESS_H__

#include "rtcdate.h"

void rtcacc_init(void);
void rtcacc_deinit(void);
int rtcacc_get(rtcdate_t * rtcdate);
int rtcacc_set(rtcdate_t *rtcdate);

#endif /*__RTCACCESS_H__ */
