/**
 * @file filefolder.c
 * @author Napat Rungruangbangchan
 * @date 12 November 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int lsdir(const char* dir){
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
	char buf[512];
	
	mydir = opendir(dir);
	if( mydir == NULL){		
		return -1;
	}
    while((myfile = readdir(mydir)) != NULL){
        sprintf(buf, "%s/%s", dir, myfile->d_name);
		stat(buf, &mystat);
		// to use %zu or %lu for size_t: https://stackoverflow.com/a/41264434/3616311
        printf("%lu\t%s\n", (unsigned long)mystat.st_size, myfile->d_name);
    }
	closedir(mydir);
	return 0;
}

int lsdir_buf(const char* dir, char* out_buf, int* lscount){
    DIR *mydir;
    struct dirent *myfile;
   // struct stat mystat;
    //char buf[512];
    int len = 0;
	
	mydir = opendir(dir);
	if( mydir == NULL){		
		return -1;
    }
    *lscount = 0;
    while((myfile = readdir(mydir)) != NULL){
        len += sprintf(&out_buf[len], "%s\n", myfile->d_name) + 1;
        *lscount = *lscount + 1;
    }
	closedir(mydir);
    //printf("%d:%d:%s", *lscount, len, out_buf);

	return 0;
}
