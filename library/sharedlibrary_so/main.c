/**
 * @file main.c
 * @author Napat Rungruangbangchan
 * @date 11 September 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <systemcall.h>

int main(int argc, char * argv[]){

	// Call function defined in dynamic lib .so
	printf("------------------------------------\n");
	system_printf("ls -al");
	printf("------------------------------------\n");

	return 0;
}

