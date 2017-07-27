/**
 * @file main.c
 * @author Napat Rungruangbangchan
 * @date 27 July 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "sgdbm.h"

void sdb_help(){
	fprintf(	stdout,
				"Example\n" 
				" ./binary insert hashkey1 1 firstname lastname city 1986\n"
				" ./binary update key1 2 fname lname city 1987\n"
				" ./binary delete key1\n" 
				" ./binary show key1\n"
				// " ./binary showall\n"
			);
}

int main(int argc, char * argv[]){
	int ret;
	GDBM_FILE gdbm_fd = NULL;
	sgdbm_record_t srec;
	char key[20];

	if( argc > 1){
		if(argc > 7 && (!strcmp(argv[1], "insert") || !strcmp(argv[1], "update")) ) {
			// ./binary insert key1 1 fname lname city 1986 
			// ./binary update key1 2 fname lname city 1987 
			gdbm_fd = sgdbm_open(DB_FILENAME);
			strncpy(key, argv[2], sizeof(key));
			srec.id = atoi(argv[3]);
			strcpy(srec.firstname, argv[4]);
			strcpy(srec.lastname, argv[5]);
			strcpy(srec.city, argv[6]);
			srec.yearofbirth = atoi(argv[7]);

			if(!strcmp(argv[1], "insert")){
				ret = sgdbm_insert(gdbm_fd, key, &srec);			
				if(ret == 0){
					fprintf(stdout, "Insert key %s complete!!\n", key);
				}
			}else{ // update
				ret = sgdbm_update(gdbm_fd, key, &srec);			
				if(ret == 0){
					fprintf(stdout, "Update key %s complete!!\n", key);
				}
			}
			
		}else if(argc > 2 && !strcmp(argv[1], "delete")) {
			// ./binary delete key1
			gdbm_fd = sgdbm_open(DB_FILENAME);
			strncpy(key, argv[2], sizeof(key));
			sgdbm_del(gdbm_fd, key);			

		}else if(argc > 2 && !strcmp(argv[1], "show")) {
			// ./binary show key1
			strncpy(key, argv[2], sizeof(key));
			gdbm_fd = sgdbm_open(DB_FILENAME);
			ret = sgdbm_get(gdbm_fd, key, &srec);
			if( ret <= 0) {
				fprintf(stderr, "%s(%d) ERROR! key %s not found!!\n\n", __FUNCTION__, __LINE__, key);
				sdb_help();
				sgdbm_close(gdbm_fd);
				return -1;
			}else if( ret < 0) {
				fprintf(stderr, "%s(%d) unknown ERROR!\n\n", __FUNCTION__, __LINE__);
				sdb_help();
				sgdbm_close(gdbm_fd);
				return -1;				
			}
			fprintf(stdout, "KEY: %s\n", key);
			fprintf(stdout, "\t id: %d\n", srec.id);
			fprintf(stdout, "\t firstname: %s\n", srec.firstname);	
			fprintf(stdout, "\t lastname: %s\n", srec.lastname);	
			fprintf(stdout, "\t city: %s\n", srec.city);
			fprintf(stdout, "\t yearofbirth: %d\n", srec.yearofbirth);		
			fprintf(stdout, "\n");	
//
//		}else if(argc > 1 && !strcmp(argv[1], "showall")) {
//			// ./binary showall
//			off_t curpos = 0;			
//			gdbm_fd = sdb_open_append(DB_FILENAME);
//			while( sdb_record_getnext(gdbm_fd,&srec, &curpos) > 0){
//				fprintf(stdout, "key id: %d\n", srec.id);
//				fprintf(stdout, "firstname: %s\n", srec.firstname);	
//				fprintf(stdout, "lastname: %s\n", srec.lastname);	
//				fprintf(stdout, "city: %s\n", srec.city);
//				fprintf(stdout, "yearofbirth: %d\n", srec.yearofbirth);		
//				fprintf(stdout, "\n");
//			}

		}else{
			fprintf(stderr, "Error!! bad command or argument\n\n");
			sdb_help();
			sgdbm_close(gdbm_fd);
			return -1;
		}
	}else{
		sdb_help();
		return -1;
	}
	
	sgdbm_close(gdbm_fd);
	return ret;
}
