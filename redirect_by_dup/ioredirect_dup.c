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
	int fd_output;

	if( (fd_output = open("output.txt", O_CREAT | O_APPEND | O_WRONLY) ) < 0 ){
		perror("fd_out open");
		exit(1);
	}

	// Select what id to use by dup()
#ifdef CLOSE_STDERR
	// Select dup() to use stderr by closes the stderr of the current process
	close(STDERR_NUM);
#endif

#ifdef CLOSE_STDOUT
	// Select dup() to use stdout by closes the stdout of the current process
	close(STDOUT_NUM);
#endif	

	// redirect the lowest-number unused descriptor that is not open to point to fd_output
	dup(fd_output);

	// close old fd_output
	close(fd_output);

	fprintf(stdout, "To out.txt line 1\n");
	fprintf(stdout, "To out.txt line 2\n");
	fprintf(stderr, "To err.txt line 1\n");
	fprintf(stderr, "To err.txt line 2\n");

	return 0;
}
