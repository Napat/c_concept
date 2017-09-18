/**
 *	\file unixtime.h
 *	\brief 
 *  Created on: Feb 23, 2011
 *      Author: Napat Rungruangbangchan
 */
#ifndef _UNIXTIME_H_	
#define	 _UNIXTIME_H_

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>

//#include "arrayjj.h"	//#include "../../SHARE_LIBS/arrayjj/arrayjj.h"		



	#ifdef _UNIXTIME_C_
		pthread_mutex_t unixtime_mutex = PTHREAD_MUTEX_INITIALIZER;
	#else
		extern pthread_mutex_t unixtime_mutex;
	#endif
	

int set_timeFromBrokenDownTime(int hour, int min, int sec, int mday, int mon, int yearSince2000, int print_en_flag);
int set_timeFromBrokenDownTimeFull(	int hour,
																		int isdst,
																		int mday,
																		int min,
																		int mon,
																		int sec,
																		int tm_wday,
																		int tm_yday,
																		int yearSince1900,
																		int print_en_flag);
int get_time (time_t * sec, time_t * usec);		//void get_time (unsigned int* sec, unsigned int* usec);
void print_unixtime(time_t time_sec, time_t time_usec); 	//void print_unixtime(unsigned int time_sec, unsigned int time_usec);
char* get_unixtime(char* out, time_t time_sec, time_t time_usec);
void print_humanreadtime(time_t time_sec, time_t time_usec) ; //void print_humanreadtime(unsigned int time_sec, unsigned int time_usec);
char* get_humanreadtime(char* out, time_t time_sec, time_t time_usec);
long int getdelta_time_usec(int t2_timesec, int t2_timeusec, int t1_timesec, int t1_timeusec);

int getTimeYear();
int getTimeMonth();
int getTimeDay();
int getTimeHour();
int getTimeMin();
int getTimeSec();
int getuptime(time_t * sec, time_t * usec);
#endif
 