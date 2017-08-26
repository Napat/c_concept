/**
 * @file main.c
 * @author Napat Rungruangbangchan
 * @date 26 August 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *printer_task(void *arg);

int main(int argc, char * argv[]){
	pthread_t printer_td;
	int counter = 0;	

	while(1){
		fprintf(stdout, "counter=%d\r\n", counter);
		if((counter%10) == 0){
			fprintf(stdout, "Create new printer context\r\n");

			if( pthread_create( &printer_td, NULL, printer_task, (void *)"printer1" ) != 0 ){
				fprintf(stderr, "%s(%d) create thread ERROR!!\r\n", __FUNCTION__, __LINE__);
			}
			// Detached thread to automatic free resources to prevent memory leaks issue 
			pthread_detach(printer_td);
		}
		sleep(1);
		counter++;
	}
	return 0;
}

void *printer_task(void *arg){
	int counter;
	for(counter=0; counter<10; counter++){
		fprintf(stdout, "output from %s round %d\r\n", (char*)arg, counter );
		usleep(500000);
	}
	return NULL;
}

