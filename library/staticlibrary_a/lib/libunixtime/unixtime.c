/**
 *	\file unixtime.c
 *	\brief 
 *  Created on: Feb 23, 2011
 *      Author: Napat Rungruangbangchan
 */
#ifndef _UNIXTIME_C_	
#define	 _UNIXTIME_C_

#include "include/unixtime.h"

//hour(0–23),min(0–59),sec(0–60),mday(1–31),mon(1–12),yearSince2000, int print_en_flag(0:disable,1:enable)
int set_timeFromBrokenDownTime(int hour, int min, int sec, int mday, int mon, int yearSince2000, int print_en_flag){
	struct tm mytime;
    	struct timeval systime;
   	char * text_time;

    	mytime.tm_sec = sec;   						// tm_sec		: seconds (0 – 60, 60 = Leap second)
    	mytime.tm_min = min;   						// tm_min	: minutes (0 – 59)
    	mytime.tm_hour = hour;  					// tm_hour	: hour (0 – 23)
    	mytime.tm_mday = mday;  					// tm_mday	: day of the month (1 – 31)
    	mytime.tm_mon = mon -1;  					// tm_mon	: month (0 – 11, 0 = January)
    	mytime.tm_year = yearSince2000 + 100; 	// tm_year	: year since 1900 + 100

   	systime.tv_sec = mktime(&mytime);
    	systime.tv_usec = 0;

	// Mutex Lock
	pthread_mutex_lock(&unixtime_mutex);

   	 if(settimeofday(&systime, NULL) != 0)		//http://china.qnx.com/developers/docs/6.4.1/neutrino/lib_ref/s/settimeofday.html
	{
    		printf("Error!! settimeofday with err code %d\n",errno);	
		// Mutex Unlock
		pthread_mutex_unlock(&unixtime_mutex);	
		return -1;
	}
	 
	 // Mutex Unlock
	 pthread_mutex_unlock(&unixtime_mutex);  
		
		if(print_en_flag)
		{
		
		    /* Time of day is set.  Now, let's get it, and verify that it looks right */
		    gettimeofday(&systime, NULL);
		
		    text_time = ctime(&systime.tv_sec);
		
		    printf("The system time is set to %s\n", text_time);
		}

    return 0;

}	

/// Set system time from Calendar time (also known as "broken-down time")
//int set_timeFromBrokenDownTimeFull(int sec, int min, int hour, int mday, int mon, int year)
int set_timeFromBrokenDownTimeFull(	int hour,
																		int isdst,
																		int mday,
																		int min,
																		int mon,
																		int sec,
																		int tm_wday,
																		int tm_yday,
																		int yearSince1900,
																		int print_en_flag){
    struct tm mytime;
    struct timeval systime;
    char * text_time;

	mytime.tm_hour 	= hour;   			// hour (0 – 23)
	mytime.tm_isdst = isdst;					// Daylight saving time enabled (> 0), disabled (= 0), or unknown (< 0)
    	mytime.tm_mday 	= mday;   				// day of the month (1 – 31)
	mytime.tm_min 	= min;    						// minutes (0 – 59)
	mytime.tm_mon 	= mon;    				// month (0 – 11, 0 = January)
   	 mytime.tm_sec 	= sec;    						// seconds (0 – 60, 60 = Leap second)
  	mytime.tm_wday 	= tm_wday;				// day of the week (0 – 6, 0 = Sunday)
 	mytime.tm_yday 	= tm_yday;				// day of the year (0 – 365)
  	mytime.tm_year 	= yearSince1900; 				// year since 1900
		

    systime.tv_sec = mktime(&mytime);
    systime.tv_usec = 0;

	// Mutex Lock
	pthread_mutex_lock(&unixtime_mutex);

    	if(settimeofday(&systime, NULL) != 0)		//http://china.qnx.com/developers/docs/6.4.1/neutrino/lib_ref/s/settimeofday.html
    	{
    			printf("Error!! settimeofday with err code %d\n",errno);	
	 		// Mutex Unlock
			 pthread_mutex_unlock(&unixtime_mutex);  				
			return -1;
	}
	// Mutex Unlock
	pthread_mutex_unlock(&unixtime_mutex);	

	if(print_en_flag)
	{	
		// Mutex Lock
		pthread_mutex_lock(&unixtime_mutex);
	
		/* Time of day is set.  Now, let's get it, and verify that it looks right */
		gettimeofday(&systime, NULL);

		// Mutex Unlock
		pthread_mutex_unlock(&unixtime_mutex);	

		text_time = ctime(&systime.tv_sec);
		printf("The system time is set to %s\n", text_time);
	}
		
    return 0;

}


int get_time (time_t * sec, time_t * usec){
	struct timeval tv;
	
	// Mutex Lock
	pthread_mutex_lock(&unixtime_mutex);

	if(gettimeofday (&tv, NULL) != 0)
	{
    		printf("Error!! settimeofday with err code %d\n",errno);	
		// Mutex Unlock
		pthread_mutex_unlock(&unixtime_mutex);				
		return -1;
	}	
	// Mutex Unlock
	pthread_mutex_unlock(&unixtime_mutex);		
	*sec = tv.tv_sec;
	*usec = tv.tv_usec;
	return 0;
}

void print_unixtime(time_t time_sec, time_t time_usec){		
	printf("UnixTime_sec = %d, Time_usec = %06d\n", (int)time_sec, (int)time_usec);	
}	

char* get_unixtime(char* out, time_t time_sec, time_t time_usec){	
	sprintf(out, "UnixTime_sec = %d, Time_usec = %06d\n", (int)time_sec, (int)time_usec);	
	return out;
}

void print_humanreadtime(time_t time_sec, time_t time_usec){		
	time_t	curtime = time_sec;	
	printf("%s", ctime(&curtime));					//fputs(ctime(&curtime), stdout);			 
	//printf("Time_usec = %06d\n", (int)time_usec);
	
}	

char* get_humanreadtime(char* out, time_t time_sec, time_t time_usec) {	
	time_t	curtime = time_sec;		
	sprintf(out, "%s", ctime(&curtime));
	return out;
}

long int getdelta_time_usec(int t2_timesec, int t2_timeusec, int t1_timesec, int t1_timeusec){
	long int long_t1_timeusec, long_t2_timeusec;

	long_t1_timeusec = (t1_timesec *1000000) + t1_timeusec;
	long_t2_timeusec = (t2_timesec *1000000) + t2_timeusec;
	
	return( long_t2_timeusec - long_t1_timeusec);
}

int getTimeYear(){
	time_t t = time(NULL);
	struct tm curtime = *localtime(&t);

	return curtime.tm_year + 1900;
}

int getTimeMonth(){
	time_t t = time(NULL);
	struct tm curtime = *localtime(&t);

	return curtime.tm_mon + 1;
}

int getTimeDay(){
	time_t t = time(NULL);
	struct tm curtime = *localtime(&t);

	return curtime.tm_mday;
}

int getTimeHour(){
	time_t t = time(NULL);
	struct tm curtime = *localtime(&t);

	return curtime.tm_hour;
}

int getTimeMin(){
	time_t t = time(NULL);
	struct tm curtime = *localtime(&t);

	return curtime.tm_min;
}

int getTimeSec(){
	time_t t = time(NULL);
	struct tm curtime = *localtime(&t);

	return curtime.tm_sec;
}

int getuptime(time_t * sec, time_t * usec)
{
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	*sec = t.tv_sec;
	*usec = t.tv_nsec/1000;
	return 0;
}

/*
int main(void){
//	time_t	curtime ;
	unsigned int time_sec, time_usec;
	unsigned char hexbuff[ BIT2BYTE(32) ];
	
	while(1)
	{
			// Get Unix time
			get_time (&time_sec, &time_usec);
		
			// Display Unix time
			display_UnixTime(time_sec,time_usec);
			
			// Display human-readable time 
			display_HumanReadTime(time_sec,time_usec);
           
           
           printf("Input time data(hex) : 0x%x \n", time_sec);
			
			uintToHexByteArray(time_sec, BIT2BYTE(32) , hexbuff , LITTLE_ENDIAN);
			printf("Convert Hex data to LITTLE_ENDIAN : %x %x %x %x \n", hexbuff[0], hexbuff[1], hexbuff[2], hexbuff[3]);
			
			uintToHexByteArray(time_sec, BIT2BYTE(32) , hexbuff , BIG_ENDIAN);
			printf("Convert Hex data to BIG_ENDIAN    : %x %x %x %x \n", hexbuff[0], hexbuff[1], hexbuff[2], hexbuff[3]);
           
           printf("\n\n");
           
           sleep(1);
		
	}
	
	return 0;	
	
}	
*/
/*//Ex howto getdelta_time_usec()

			do{
				get_time((time_t*)&present_timesec, (time_t*)&present_timeusec);	
				printf("....%ld....\n", getdelta_time_usec(present_timesec, present_timeusec, lastsend_timesec, lastsend_timeusec));
			}while( getdelta_time_usec(present_timesec, present_timeusec, lastsend_timesec, lastsend_timeusec) < ( send_delay -CODING_DELAY_PAYBACK) );

*/

#endif
