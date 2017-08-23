/**
 * @file rtcaccess.c
 * @author Napat Rungruangbangchan
 * @date 14 Aguent 2017 
 * @brief This file is part of char driver sample
 * @Compiler: 
 * @License: 
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <rtcaccess.h>

#define CHAR_TEMP_NODE	"/dev/"NODENAME
#define MODULE_FPATH	"/mnt/run/driver/chardrv_template_drv.ko"

static int devfd;
static pthread_mutex_t devlock;
static char arg_buff[4096];

static void rtcacc_sync_linux(void){
	// add code
	return;
}

/**
 * @brief Init linux time and rtc environment
 * @param None. 
 */
void rtcacc_init(void){
	static char s[100];
	sprintf(s,"insmod %s", MODULE_FPATH);
	system(s);	

	sprintf(s,"mknod %s c %d %d", RTC49X_MISC_NODE, RTC_DRV_MAJOR, RTC_DRV_MINOR );
	system(s);

	if( (devfd = open(CHAR_TEMP_NODE, O_RDWR | O_SYNC | O_DSYNC | O_RSYNC) ) <= 0){
		fprintf(stderr, "%s(%d) error open driver!!\r\n", __FUNCTION__, __LINE__);
	}
	pthread_mutex_init(&devlock, NULL);
	rtcacc_sync_linux();
	fprintf(stdout, "%s(%d) complete with fd: %d\r\n", __FUNCTION__, __LINE__, devfd);
	return;
}

/**
 * @brief Deinit environment
 * @param None. 
 */
void rtcacc_deinit(void){
	close(devfd);
	devfd = 0;
	pthread_mutex_destroy(&devlock);
}

/**
 * @brief Get time from driver
 * @param rtcdate Date/Time information to get. 
 */
int rtcacc_get(rtcdate_t * rtcdate){
	rtcdev_arg_t header;

	pthread_mutex_lock(&devlock);
	memset(&header, 0, sizeof(header));
	header.api_arg = (void *)arg_buff;

	if(ioctl(devfd, RTC_GETTIME, &header) >= 0){
		if(header.iserr != 0){
			fprintf(stderr, "%s(%d) Error!!!\r\n", __FUNCTION__, __LINE__);
			pthread_mutex_unlock(&devlock);
			return -1;	
		}
	}
	memcpy((char*)rtcdate, arg_buff, sizeof(*rtcdate));
	pthread_mutex_unlock(&devlock);
	return 0;	
}

/**
 * @brief Get time from driver
 * @param rtcdate Date/Time information to set. 
 */
int rtcacc_set(rtcdate_t *rtcdate){
	rtcdev_arg_t devarg;

	pthread_mutex_lock(&devlock);
	memset(&devarg, 0, sizeof(devarg));
	devarg.api_arg = (void *)rtcdate;

	if(ioctl(devfd, RTC_SETTIME, &devarg) >= 0){
		if(devarg.iserr != 0){
			fprintf(stderr, "%s(%d)\r\n", __FUNCTION__, __LINE__);
			pthread_mutex_unlock(&devlock);
			return -1;	
		}
	}
	pthread_mutex_unlock(&devlock);
	return 0;	
}
