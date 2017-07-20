/**
 * @file string_toupperlower.c
 * @author Napat Rungruangbangchan
 * @date 20 July 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <ctype.h>

char* string_toupper(char* str){
	char * p = str;	
	while(*p != '\0'){
		*p = (char) toupper((char)*p);
		p++;
	}
	return str;
}

char* string_tolower(char* str){
	char * p = str;	
	while(*p != '\0'){
		*p = (char) tolower((char)*p);
		p++;
	}
	return str;
}

int main(int argc, char * argv[]){
	char string[] = "HELlo wOrlD!";

	fprintf(stdout, "%s\n", string_toupper(string));
	fprintf(stdout, "%s\n", string_tolower(string));

	return 0;
}
