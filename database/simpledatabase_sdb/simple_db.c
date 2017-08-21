/**
 * @file simple_db.c
 * @author Napat Rungruangbangchan
 * @date 23 July 2017 
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

#define DB_FILENAME		"customers.sdb"
#define DBTMP_FILENAME	"tmp."DB_FILENAME

typedef struct sdb_record_s {
	unsigned int kid;
	char	firstname[16];
	char	lastname[16];
	char	city[16];
	int 	yearofbirth;
} sdb_record_t;

/**
 * @brief Open sdb file for append new record to db
 * 
 * @return negative when error, otherwise return fd number
 */
int sdb_open_append(char * db_fname) {
	int fd;

	fd = open(db_fname, O_CREAT | O_RDWR | O_APPEND, 0644);
	if(fd == -1){
		fprintf(stderr, "%s(%d) error! filename %s\n", __FUNCTION__, __LINE__, db_fname);
		return -1;
	}
	return fd;
}

/**
 * @brief Open sdb file for update(edit/delete) any old record in db
 * 
 * @return negative when error, otherwise return fd number
 */
int sdb_open_update(char * db_fname) {
	int fd;

	fd = open(db_fname, O_CREAT | O_RDWR, 0644);
	if(fd == -1){
		fprintf(stderr, "%s(%d) error! filename %s\n", __FUNCTION__, __LINE__, db_fname);
		return -1;
	}
	return fd;
}

/**
 * @brief 
 * 
 */
void sdb_close(int * fd) {
	if(*fd != -1){
		close(*fd);
		*fd = -1;
	}	
}

/**
 * @brief 
 * 
 * @return negative when error, otherwise return write number
 */
int sdb_insert(int fd, sdb_record_t * srec) {
	int ret;
	ret = write(fd, srec, sizeof(*srec));
	return ret;
}

/**
 * @brief get record by kid
 * 
 * @return sizeof sdb_record_t , -1 if error, 0 if record not found 
 */
int sdb_record_get(int fd, int kid, sdb_record_t * srec) {
	int ret;
	while((ret = read(fd, srec, sizeof(*srec))) != -1){
		if( ret == 0 ){
			//eof: not found
			return 0;
		}else if(kid == srec->kid){
			//found
			return ret;
		}
	}
	//error
	return -1;
}

/**
 * @brief get next record by kid
 * 
 * @return sizeof sdb_record_t , -1 if error, 0 eof
 */
int sdb_record_getnext(int fd, sdb_record_t * srec, off_t * curpos) {
	int ret;	
	*curpos = lseek(fd, *curpos, SEEK_SET);
	while((ret = read(fd, srec, sizeof(*srec))) != -1){
		if( ret == 0 ){
			//eof: not found
			return 0;
		}
		// now cur is on next pos then set cur to curpos
		*curpos = lseek(fd, 0, SEEK_CUR);
		return ret;
	}
	//error
	return -1;
}

static int delete_a_record_by_kid_copyrenamemethod(int * pfd, int kid) {
// this method is not efficient for large file size but still be ok for small file
	int ret;
	sdb_record_t srec;
	int fd_tmp = -1;

	// remove old & new tmp file
	remove(DBTMP_FILENAME);
	fd_tmp = sdb_open_append(DBTMP_FILENAME);

	// start copy to tmp file from beginning
	lseek(*pfd, 0, SEEK_SET);
	while((ret = read(*pfd, &srec, sizeof(srec))) != -1) {
		if( ret == 0 ){
			//eof: complete
			sdb_close(pfd);
			sdb_close(&fd_tmp);
			remove(DB_FILENAME);
			rename(DBTMP_FILENAME, DB_FILENAME);
			return sizeof(srec);

		}else if(kid == srec.kid){
			// skip copy
		}else{
			// copy to tmpfile
			ret = write(fd_tmp, &srec, sizeof(srec));
		}		
	}
	sdb_close(&fd_tmp);
	remove(DBTMP_FILENAME);
	fprintf(stderr, "%s(%d) unknown ERROR!!\n", __FUNCTION__, __LINE__);
	return -1;
}

/**
 * @brief 
 * 
 * @return sizeof sdb_record_t , -1 if error, 0 if record not found 
 */
int sdb_delete(int * pfd, int kid){
	int ret;
	sdb_record_t srec;
	off_t pos;

	pos = lseek(*pfd, 0, SEEK_SET);
	while((ret = read(*pfd, &srec, sizeof(srec))) != -1) {
		if( ret == 0 ){
			//eof: not found
			return 0;
		}else if(kid == srec.kid){
			//found
			if(0){ // method 1: fill zero to kis method
				lseek(*pfd, pos, SEEK_SET);					// move back to current record pos.
				srec.kid = 0;								// mark key id as 0 **This is bad idea. It is not a delete. It just a mark to zero. Need to be improve.
															// see method 2: deleting a record from a binary file by create & rename method
															// but create & rename method still not efficient for large db file!!
				ret = write(*pfd, &srec, sizeof(srec));						
			
			}else { // method 2: deleting a record from a binary file by create & rename method
				ret = delete_a_record_by_kid_copyrenamemethod(pfd, kid);
			}

			return ret;
		}
		// set cur to pos for next round
		pos = lseek(*pfd, 0, SEEK_CUR);
	}
	//error
	return -1;
}

void sdb_help(){
	fprintf(	stdout,
				"Example\n" 
				"./binary insert 1 Myfirstname Mylastname Newyork 1986\n"
				"./binary delete 1\n" 
				"./binary show 1\n"
				"./binary showall\n"
			);
}

int main(int argc, char * argv[]){
	int ret;
	int fd = -1;
	sdb_record_t srec;

	if( argc > 1){
		if(argc > 6 && !strcmp(argv[1], "insert")) {
			// ./binary insert 1 fname lname city year 
			fd = sdb_open_append(DB_FILENAME);
			srec.kid = atoi(argv[2]);
			strcpy(srec.firstname, argv[3]);
			strcpy(srec.lastname, argv[4]);
			strcpy(srec.city, argv[5]);
			srec.yearofbirth = atoi(argv[6]);
			sdb_insert(fd, &srec);			

		}else if(argc > 2 && !strcmp(argv[1], "delete")) {
			// ./binary delete 1
			fd = sdb_open_update(DB_FILENAME);
			sdb_delete(&fd, atoi(argv[2]));			

		}else if(argc > 2 && !strcmp(argv[1], "show")) {
			// ./binary show 1
			unsigned int kid = atoi(argv[2]);
			fd = sdb_open_append(DB_FILENAME);
			ret = sdb_record_get(fd, kid, &srec);
			if( ret == 0) {
				fprintf(stderr, "%s(%d) ERROR! kid(%d) not found!!\n", __FUNCTION__, __LINE__, kid);
				sdb_help();
				sdb_close(&fd);
				return -1;
			}else if( ret < 0) {
				fprintf(stderr, "%s(%d) unknown ERROR!\n", __FUNCTION__, __LINE__);
				sdb_help();
				sdb_close(&fd);
				return -1;				
			}
			fprintf(stdout, "key id: %d\n", srec.kid);
			fprintf(stdout, "firstname: %s\n", srec.firstname);	
			fprintf(stdout, "lastname: %s\n", srec.lastname);	
			fprintf(stdout, "city: %s\n", srec.city);
			fprintf(stdout, "yearofbirth: %d\n", srec.yearofbirth);		

		}else if(argc > 1 && !strcmp(argv[1], "showall")) {
			// ./binary showall
			off_t curpos = 0;			
			fd = sdb_open_append(DB_FILENAME);
			while( sdb_record_getnext(fd,&srec, &curpos) > 0){
				fprintf(stdout, "key id: %d\n", srec.kid);
				fprintf(stdout, "firstname: %s\n", srec.firstname);	
				fprintf(stdout, "lastname: %s\n", srec.lastname);	
				fprintf(stdout, "city: %s\n", srec.city);
				fprintf(stdout, "yearofbirth: %d\n", srec.yearofbirth);		
				fprintf(stdout, "\n");
			}

		}else{
			fprintf(stderr, "Error!! bad command or argument\n");
			sdb_help();
			sdb_close(&fd);
			return -1;
		}
	}else{
		sdb_help();
		return -1;
	}
	
	sdb_close(&fd);
	return 0;
}
