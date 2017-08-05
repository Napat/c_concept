// rtcdate.h
// 

#ifndef __RTCDATE_H__
#define __RTCDATE_H__

typedef unsigned char U8INT_RTC;

typedef struct rtcdate_s{
	U8INT_RTC sec;			// sec: 00-59
	U8INT_RTC min;			// min: 00-59
	U8INT_RTC hour;			// hour: 0-23
	U8INT_RTC date;			// date: 1-31
	U8INT_RTC mon;			// month: 1-12
	U8INT_RTC year;			// year: 00-99: 2000 to 2099
	U8INT_RTC dayofweek;	// dayofweek: 1-7: user-defined but must be sequential,i.e., 1: Sunday 2: Monday ...	
}rtcdate_t;

#define	RTC_IOCTL_BASE	'p'
#define	RTC_GETTIME		_IOR(RTC_IOCTL_BASE, 	0, rtcdate_t)
#define RTC_SETTIME		_IOWR(RTC_IOCTL_BASE, 	1, rtcdate_t)	

#endif /* __RTCDATE_H__ */
