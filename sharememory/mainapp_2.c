/**
 * @file mainapp_1.c
 * @author Napat Rungruangbangchan
 * @date 2 Septerber 2017 
 * @brief Sharemem example
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ipc_handler.h"

static int shm_init_attacher(ipc_handler_t *handler, int shm_key){
	int shmid;

	fprintf(stdout, "%s:%s Attach shared memory with size %lu.\r\n", __FILE__, __FUNCTION__, sizeof(ipc_sharemem_t));
	shmid = shmget(shm_key, sizeof(ipc_sharemem_t), 0666);
	if(shmid < 0){		
		perror("shmget");
		fprintf(stderr, "%s:%s Error!!\r\n", __FILE__, __FUNCTION__);
		return -1;
	}

	// Attaches shared memory segment
	handler->shm_ptr = shmat(shmid, NULL, 0);
	if(handler->shm_ptr == (ipc_sharemem_t *)-1 ){
		perror("shmat");
		fprintf(stderr, "%s:%s Error!!\r\n", __FILE__, __FUNCTION__);	
		return -2;
	}

	return 0;	
}

int main(int argc, char * argv[]){
	ipc_handler_t ipc_handler;

	if(shm_init_attacher(&ipc_handler, IPC_SHAREMEM_KEY) != 0){
		exit(1);
	}

	// Read data in share memory
	printf("%s(%d): temp1=%d\r\n", 		__FILE__, __LINE__, ipc_handler.shm_ptr->temp[0].temp);
	printf("%s(%d): temp2=%d\r\n", 		__FILE__, __LINE__, ipc_handler.shm_ptr->temp[1].temp);
	printf("%s(%d): fan1.level=%d\r\n", __FILE__, __LINE__, ipc_handler.shm_ptr->fan[0].level);
	printf("%s(%d): fan1.rpm=%d\r\n", 	__FILE__, __LINE__, ipc_handler.shm_ptr->fan[0].speed_rpm);
	printf("%s(%d): fan2.level=%d\r\n", __FILE__, __LINE__, ipc_handler.shm_ptr->fan[1].level);
	printf("%s(%d): fan2.rpm=%d\r\n", 	__FILE__, __LINE__, ipc_handler.shm_ptr->fan[1].speed_rpm);

	// Write data to share memory
	ipc_handler.shm_ptr->temp[0].temp = 28;
	ipc_handler.shm_ptr->temp[1].temp = 29;
	ipc_handler.shm_ptr->fan[0].level = ipc_handler.shm_ptr->fan[0].level + 1;
	ipc_handler.shm_ptr->fan[0].speed_rpm = 999;
	ipc_handler.shm_ptr->fan[1].level = ipc_handler.shm_ptr->fan[1].level + 1;
	ipc_handler.shm_ptr->fan[1].speed_rpm = 1000;

	return 0;
}


