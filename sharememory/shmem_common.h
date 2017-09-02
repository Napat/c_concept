/**
 * @file sharemem_common.h
 * @author Napat Rungruangbangchan
 * @date 2 Septerber 2017 
 * @brief Sharemem example
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */
#ifndef _SHAREMEM_COMMON_H_
#define _SHAREMEM_COMMON_H_

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include <stdint.h>

#define IPC_SHAREMEM_KEY		8888

#define TEMPSENSOR_COUNT		(2)
typedef struct{
	int8_t 		temp;
} tempsensor_t;

#define FAN_COUNT				(2)
typedef struct{
	uint8_t 	level;
	uint16_t 	speed_rpm;
} fanmodule_t;

typedef struct{
	tempsensor_t 		temp[TEMPSENSOR_COUNT];
	fanmodule_t			fan[FAN_COUNT];
} ipc_sharemem_t;

#endif /* _SHAREMEM_COMMON_H_ */
