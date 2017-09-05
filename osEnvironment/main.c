/**
 * @file main.c
 * @author Napat Rungruangbangchan
 * @date 2 September 2017 
 * @brief  
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

extern char** environ;

void env_listall(void){
	char** var;
	for(var = environ; *var != NULL; var++){
		fprintf(stdout, "%s\n", *var);
	}
	return;
}

int main(int argc, char * argv[]){
	char * env = NULL;
	int mytcpport;

	printf("\r\n---Part 1---------------------\r\n");
	env_listall();
	setenv("MYPROGRAM_TCPPORT", "4321", 1);
	printf("\r\n++++\r\n");
	system("env | grep MYPROGRAM_TCPPORT");
	
	printf("\r\n---Part 2---------------------\r\n");
	env = getenv("MYPROGRAM_TCPPORT");
	if(env == NULL){
		printf("Not found environment variable: MYPROGRAM_TCPPORT\r\n");
		//Use default setting
		mytcpport = 4444;
	}else{
		mytcpport = strtol(env, (char **)NULL, 10);
	}	
	printf("Now using tcp port: %d\r\n", mytcpport);

	printf("\r\n---Part 3---------------------\r\n");
	unsetenv("MYPROGRAM_TCPPORT");
	env = getenv("MYPROGRAM_TCPPORT");
	if(env == NULL){
		printf("Not found environment variable: MYPROGRAM_TCPPORT\r\n");
		//Use default setting
		mytcpport = 4444;
	}else{
		mytcpport = strtol(env, (char **)NULL, 10);
	}	
	printf("Now using tcp port: %d\r\n", mytcpport);
	
	return 0;
}
