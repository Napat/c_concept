/**
 * @file main.c
 * @author Napat Rungruangbangchan
 * @date 24 August 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <pthread.h>

void *myprinter1(void *arg);
void *myprinter2(void *arg);

int main(int argc, char * argv[]){
	pthread_t printer1_td, printer2_td;
	int ret;

	//////////////////////////////////////
	// pthread & join without return value 
	//////////////////////////////////////

	fprintf(stdout, "[---01-------------------------]\r\n");

	if( pthread_create( &printer1_td, NULL, myprinter1, (void *)"printer1" ) != 0 ){
		fprintf(stderr, "%s(%d) create thread ERROR!!\r\n", __FUNCTION__, __LINE__);
	}

	fprintf(stdout, "%s(%d)\r\n", __FUNCTION__, __LINE__ );
	// join the thread, the caller is garanteed that target thread has terminated.
	pthread_join(printer1_td, NULL);
	fprintf(stdout, "%s(%d)\r\n", __FUNCTION__, __LINE__);
	
	//////////////////////////////////////
	// pthread & join with return value 
	//////////////////////////////////////

	fprintf(stdout, "[---02-------------------------]\r\n");
	
	if( pthread_create( &printer2_td, NULL, myprinter2, (void *)"printer2" ) != 0 ){
		fprintf(stderr, "%s(%d) create thread ERROR!!\r\n", __FUNCTION__, __LINE__);
	}

	fprintf(stdout, "%s(%d)\r\n", __FUNCTION__, __LINE__ );
	pthread_join(printer2_td, (void**)&ret);

	fprintf(stdout, "%s(%d) return value of thread is %d\r\n", __FUNCTION__, __LINE__, ret);


	fprintf(stdout, "----------------------------\r\n");
	return 0;
}

void *myprinter1(void *arg){
	int counter;
	for(counter=0; counter<10; counter++){
		fprintf(stdout, "%s: %d\r\n", (char*)arg, counter );
	}
	return NULL;
}

void *myprinter2(void *arg){
	int counter;
	for(counter=0; counter<10; counter++){
		fprintf(stdout, "%s: %d\r\n", (char*)arg, counter );
	}
	return (void*)-1;
}
