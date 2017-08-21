/**
 * @file gdbmwrapper.c
 * @author Napat Rungruangbangchan
 * @date 22 July 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <string.h>
#include "gdbmwrapper.h"

#define GDBMAUTO_BLOCKSIZE	(0)

/**
 * @brief open gdbm
 * 
 * @return on error return NULL, otherwise return GDBM_FILE fd
 */
GDBM_FILE dtm_open(char * db_fname){
	GDBM_FILE gdbm_fd;	
	// create gdbm database file with smallest blocksize(auto)
	gdbm_fd = gdbm_open(db_fname, GDBMAUTO_BLOCKSIZE, GDBM_WRCREAT | GDBM_READER , 0660, 0);
	if(gdbm_fd == NULL){
		fprintf(stderr, "%s(%d) error\n", __FUNCTION__, __LINE__);
		return NULL;
	}
	return gdbm_fd;
}

/**
 * @brief close gdbm
 * 
 * @return void
 */
void dtm_close(GDBM_FILE gdbm_fd){
	gdbm_close(gdbm_fd);	
	return;
}

/**
 * @brief To prepare key or data to be insert to gdbm
 * 
 * @return on success return 0, otherwise error
 */
int dtm_set(datum * dtm, char * dat, int size){
	dtm->dptr = dat;
	dtm->dsize = size;
	return 0;
}

/**
 * @brief To get value(data and size) from datum type
 * 
 * @return on success return 0, otherwise error
 */
int dtm_get(datum * dtm, char * dat, int size){
	strcpy(dat, dtm->dptr);
	size = dtm->dsize;
	return 0;
}

/**
 * @brief To get value(data) from datum type
 * 
 * @return data
 */
char * dtm_getdat(datum * dtm){
	return dtm->dptr;
}

/**
 * @brief To get value(size) from datum type
 * 
 * @return size
 */
int dtm_getdsize(datum * dtm){
	return dtm->dsize;
} 

/**
 * @brief To insert new key with data
 * Only insert data if key is not available in database
 * 
 * @return on success return 0, otherwise error
 */
int dtm_insert(GDBM_FILE * gdbm_fd, datum * key, datum * dat){
	return gdbm_store(*gdbm_fd, *key, *dat, GDBM_INSERT);
}

/**
 * @brief To replace data if key exist
 * 
 * @return on success return 0, otherwise error
 */
int dtm_replace(GDBM_FILE * gdbm_fd, datum * key, datum * dat){
	return gdbm_store(*gdbm_fd, *key, *dat, GDBM_REPLACE);
}

// Retrieve data by key
/**
 * @brief Retrieve data by key
 * Get data by key
 * 
 * @return data on success
 */
datum dtm_retrieve(GDBM_FILE * gdbm_fd, datum * key){
	return gdbm_fetch(*gdbm_fd, *key);
}

/**
 * @brief To delete data by key
 *
 * @return on success return 0, otherwise error
 */
int dtm_delete(GDBM_FILE * gdbm_fd, datum * key){
	return gdbm_delete(*gdbm_fd, *key);
}

/**
 * @brief Get first key of data in db
 *
 * @return on success return datum of firstkey
 */
datum dtm_key_first(GDBM_FILE gdbm_fd){
	return gdbm_firstkey(gdbm_fd);
}

/**
 * @brief Get next key of data in db
 *
 * @return on success return datum of nextkey
 */
datum dtm_key_next(GDBM_FILE gdbm_fd, datum current_key){
	return gdbm_nextkey(gdbm_fd, current_key);
}
