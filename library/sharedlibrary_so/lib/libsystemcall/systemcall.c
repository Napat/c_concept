/**
 *	\file systemcall.c
 *	\brief 
 *  Created on: April 3, 2013
 *      Author: Napat Rungruangbangchan
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>			// for using WEXITSTATUS() ......http://linux.die.net/man/3/system
#include <sys/wait.h>

#include "include/systemcall.h"

#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

//#define PRINTF(...)		do {  		fprintf(stderr, __VA_ARGS__); 	} while (0)
#define PRINTF(...)		do {  if(0) fprintf(stderr, __VA_ARGS__); 	} while (0)

int system_printf(const char *cmd_va, ...) {
	char cmd_line[320];	
	va_list args;																			
	int retval;
	
	va_start (args, cmd_va);
	vsprintf(cmd_line, cmd_va, args);
	
	if((retval = WEXITSTATUS(system(cmd_line))) != 0) {
		va_end (args);
		PRINTF("%s() Error, system(\"%s\") code: %d\n", __FUNCTION__,cmd_line, retval);
		return(retval);
	}	
	va_end (args);

	return(retval);	
}	


int system_sync_printf(const char *cmd_va, ...) {
	char cmd_line[320];	
	va_list args;																			
	int retval;
	
	va_start (args, cmd_va);
	vsprintf(cmd_line, cmd_va, args);
	
	if((retval = WEXITSTATUS(system(cmd_line))) != 0) {
		va_end (args);
		PRINTF("%s() in %s Error, system(\"%s\") code: %d\n", __FUNCTION__, __FILE__ ,cmd_line, retval);
		return(retval);
	}	
	va_end (args);

	if((retval = system("sync")) != 0) {
		PRINTF("%s() in %s Error, system(\"sync\") code: %d\n", __FUNCTION__, __FILE__, retval);
		return(retval);
	}	
	va_end (args);

	return(retval);	
}	

int isAccessFile(const char* filename) {
	if( access( filename, F_OK ) != -1 ) {
	    // file exists
	    return 1;
	}
	// file doesn't exist
	return 0;
}


int isAccessDir(const char* filename) {
	DIR* dir = opendir(filename);

	if(dir) {
	  	//printf("%s() Directory %s exists.\n", __FUNCTION__,filename);
		closedir(dir);
		return 1;
	} else if (ENOENT == errno) {
		closedir(dir);
		//printf("%s() Directory %s dose not exist.\n", __FUNCTION__,filename);
		return 0;
	} else { 
		//printf("%s() Open directory %s dose not exist.\n", __FUNCTION__,filename);
		return -1;
	}
}
