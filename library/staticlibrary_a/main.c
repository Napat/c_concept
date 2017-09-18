/**
 * @file main.c
 * @author Napat Rungruangbangchan
 * @date 12 September 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <unixtime.h>

int main(int argc, char* argv[]){
	time_t sec, usec;
	get_time (&sec, &usec);
	print_humanreadtime(sec, usec);

	return 0;
}


