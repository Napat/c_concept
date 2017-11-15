/**
 * @file main.c
 * @author Napat Rungruangbangchan
 * @date 15 November 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define  MSG_TX		"Hello world!"

int main(){
	pid_t pid;
	int pipefd[2], *pipefd_w, *pipefd_r;
	char buf[100];
	int ret; 

	ret = pipe(pipefd);		// pipe() return two fd, array [0] to read and [1] to write end of the pipe 
	if(ret != 0){
		perror("pipe");
		exit(1);
	}
	pipefd_r = &pipefd[0];
	pipefd_w = &pipefd[1];	

	pid = fork();
	if(pid == 0){
		printf("Child process\n");
		write(*pipefd_w, MSG_TX, sizeof(MSG_TX));		
	}else{
		printf("Parent process\n");
		read(*pipefd_r, buf, sizeof(buf));
		printf("Rx data: %s\n", buf);
	}

	printf("End, pid=%d\n", pid);
	close(*pipefd_r);
	close(*pipefd_w);
	return 0;
} 
