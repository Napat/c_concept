/**
 * @file ipc_handler.h
 * @author Napat Rungruangbangchan
 * @date 2 Septerber 2017 
 * @brief Sharemem example
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */
#ifndef _IPC_HANDLER_H_
#define _IPC_HANDLER_H_

#include "shmem_common.h"

typedef struct
{
	ipc_sharemem_t *shm_ptr;
	//int msgq_own_id;
	//int msgq_partner_id;
	//bool debug_en;
} ipc_handler_t;

#endif /* _IPC_HANDLER_H_ */
