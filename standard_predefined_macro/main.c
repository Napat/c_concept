/**
 * @file main.c
 * @author Napat Rungruangbangchan
 * @date 1 September 2017 
 * @brief Standard predefined macro example
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>

void myprinter(){
	fprintf(stdout, "%s(%d)\r\n", __func__, __LINE__);
	
	// GCC (the "Gnu Compiler Collection") also defines __FUNCTION__ and __PRETTY_FUNCTION__. 
	// These are both the same as __func__ for C. For C++, __PRETTY_FUNCTION__ is something different.
	fprintf(stdout, "%s(%d)\r\n", __FUNCTION__, __LINE__);
	fprintf(stdout, "%s(%d)\r\n", __PRETTY_FUNCTION__, __LINE__);

	return;
}

int main(int argc, char *argv[]){
	fprintf(stdout, "%s(%d) file name: %s\r\n", 	__FUNCTION__, __LINE__, __FILE__);
	fprintf(stdout, "%s(%d) compile date: %s\r\n", 	__FUNCTION__, __LINE__, __DATE__);
	fprintf(stdout, "%s(%d) compile time: %s\r\n", 	__FUNCTION__, __LINE__, __TIME__);

	myprinter();

	return 0;
}
