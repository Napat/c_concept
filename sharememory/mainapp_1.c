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
#include <string.h>
#include "ipc_handler.h"

static int shm_init_creater(ipc_handler_t *handler, int shm_key){
	int shmid;

	fprintf(stdout, "%s:%s Create shared memory with size %lu.\r\n", __FILE__, __FUNCTION__, sizeof(ipc_sharemem_t));
	shmid = shmget(shm_key, sizeof(ipc_sharemem_t), 0666 | IPC_CREAT);
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

	// Clean share memory
	memset(handler->shm_ptr, 0, sizeof(ipc_sharemem_t));

	return 0;	
}

int main(int argc, char * argv[]){
	ipc_handler_t ipc_handler;
	char cmd[50];

	if(shm_init_creater(&ipc_handler, IPC_SHAREMEM_KEY) != 0){
		exit(1);
	}

	system("ipcs -m");

	printf("--------------------\r\n"); 

	// Init default data to share memory
	ipc_handler.shm_ptr->temp[0].temp = 0;
	ipc_handler.shm_ptr->temp[1].temp = 0;
	ipc_handler.shm_ptr->fan[0].level = 1;
	ipc_handler.shm_ptr->fan[0].speed_rpm = 0;
	ipc_handler.shm_ptr->fan[1].level = 2;
	ipc_handler.shm_ptr->fan[1].speed_rpm = 0;

	// Read data in share memory
	printf("%s(%d): temp1=%d\r\n", 		__FILE__, __LINE__, ipc_handler.shm_ptr->temp[0].temp);
	printf("%s(%d): temp2=%d\r\n", 		__FILE__, __LINE__, ipc_handler.shm_ptr->temp[1].temp);
	printf("%s(%d): fan1.level=%d\r\n", __FILE__, __LINE__, ipc_handler.shm_ptr->fan[0].level);
	printf("%s(%d): fan1.rpm=%d\r\n", 	__FILE__, __LINE__, ipc_handler.shm_ptr->fan[0].speed_rpm);
	printf("%s(%d): fan2.level=%d\r\n", __FILE__, __LINE__, ipc_handler.shm_ptr->fan[1].level);
	printf("%s(%d): fan2.rpm=%d\r\n", 	__FILE__, __LINE__, ipc_handler.shm_ptr->fan[1].speed_rpm);

	printf("--------------------\r\n"); 

	// Run app2 that will access(read & write) the same share memory segment   
	system("./shmem_2");

	printf("--------------------\r\n"); 
	
	// Read data in share memory
	printf("%s(%d): temp1=%d\r\n", 		__FILE__, __LINE__, ipc_handler.shm_ptr->temp[0].temp);
	printf("%s(%d): temp2=%d\r\n", 		__FILE__, __LINE__, ipc_handler.shm_ptr->temp[1].temp);
	printf("%s(%d): fan1.level=%d\r\n", __FILE__, __LINE__, ipc_handler.shm_ptr->fan[0].level);
	printf("%s(%d): fan1.rpm=%d\r\n", 	__FILE__, __LINE__, ipc_handler.shm_ptr->fan[0].speed_rpm);
	printf("%s(%d): fan2.level=%d\r\n", __FILE__, __LINE__, ipc_handler.shm_ptr->fan[1].level);
	printf("%s(%d): fan2.rpm=%d\r\n", 	__FILE__, __LINE__, ipc_handler.shm_ptr->fan[1].speed_rpm);

	printf("--------------------\r\n"); 

	// Clear resources
	sprintf(cmd, "ipcrm -M %d", IPC_SHAREMEM_KEY);
	system(cmd);
	system("ipcs -m");

	printf("--------------------\r\n"); 

	return 0;
}

