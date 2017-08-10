/**
 * @file ioredirect_dup.c
 * @author Napat Rungruangbangchan
 * @date 9 August 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// Define system default file ids in integers
// Option1
// #define STDIN_NUM	(0)
// #define STDOUT_NUM	(1)
// #define STDERR_NUM	(2)
// Option2
#define STDIN_NUM	(fileno(stdin))
#define	STDOUT_NUM	(fileno(stdout))
#define STDERR_NUM	(fileno(stderr))

int main(int argc, char * argv[]){
	int fd_out, fd_err;

	// closes standard output for the current process
	// This is NOT necessary but preferred before using dup2()
	close(STDOUT_NUM);
	
	// closes standard error for the current process
	// This is NOT necessary but preferred before using dup2()
	close(STDERR_NUM);

	if( (fd_out = open("out.txt", O_CREAT | O_APPEND | O_WRONLY) ) < 0 ){
		perror("fd_out open");
		exit(1);
	}

	if( (fd_err = open("err.txt", O_CREAT | O_APPEND | O_WRONLY) ) < 0 ){
		perror("fd_err open");
		exit(1);
	}

	// Overwrite default stdout(by id number) to make them pointing to the file out.txt
	if(dup2(fd_out, STDOUT_NUM) < 0){
		perror("dup2 out");
		exit(1);
	}

	// Overwrite default stderr(by id number) to make them pointing to the file err.txt
	if(dup2(fd_err, STDERR_NUM) < 0){
		perror("dup2 err");
		exit(1);
	}

	fprintf(stdout, "To out.txt line 1\n");
	fprintf(stdout, "To out.txt line 2\n");
	fprintf(stderr, "To err.txt line 1\n");
	fprintf(stderr, "To err.txt line 2\n");

	return 0;
}
