/**
 * @file gdbm_gnudatabase.c
 * @author Napat Rungruangbangchan
 * @date 22 July 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include <stdio.h>
#include <string.h>
#include <gdbm.h>

#define GDBMAUTO_BLOCKSIZE	(0)
#define GDBM_FILENAME		"db01.gdbm"

typedef struct fullname_s{
	char first[16];
	char last[16];
} fullname_t;

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

int main(int argc, char * argv[]){
	GDBM_FILE gdbm_fd;
	datum key1, dat1_in, dat1_out; 
	datum key2, dat2_in, dat2_out;

	char k1[] = "msg1";					// do not use char *k = "..."; if you do then cannot use sizeof() to determine the array size.
	char d1[] = "Hello World!!";

	char k2[] = "msg2";
	fullname_t d2 = {"Uzumaki", "Naruto"}; 
	
	// create gdbm database file with smallest blocksize(auto)
	gdbm_fd = gdbm_open(GDBM_FILENAME, GDBMAUTO_BLOCKSIZE, GDBM_WRCREAT | GDBM_READER , 0660, 0);

	fprintf(stdout, "---------------------\r\n");	

	// prepare key and data
	dtm_set(&key1 , k1, sizeof(k1));
	dtm_set(&dat1_in , d1, sizeof(d1));
	dtm_set(&key2 , k2, sizeof(k2));
	dtm_set(&dat2_in, (char*)&d2, sizeof(d2));

	// insert new data
	if( dtm_insert(&gdbm_fd, &key1, &dat1_in) != 0){
		fprintf(stderr, "%s(%d) insert error, expect key '%s' is available in database\n", __FUNCTION__, __LINE__, dtm_getdat(&key1));
	}
	if( dtm_insert(&gdbm_fd, &key2, &dat2_in) != 0){
		fprintf(stderr, "%s(%d) insert error, expect key '%s' is available in database\n", __FUNCTION__, __LINE__, dtm_getdat(&key2));
	}

	// retrieve data back and print
	dat1_out = dtm_retrieve(&gdbm_fd, &key1);
	dat2_out = dtm_retrieve(&gdbm_fd, &key2);
	fprintf(stdout, "%s(%d) dat1=%s\n", __FUNCTION__, __LINE__, dtm_getdat(&dat1_out));
	fprintf(stdout, "%s(%d) dat2 fullname is '%s %s'\n", __FUNCTION__, __LINE__,  ((fullname_t*)dtm_getdat(&dat2_out))->first, ((fullname_t*)dtm_getdat(&dat2_out))->last);

	fprintf(stdout, "---------------------\r\n");	

	// replace data
	dtm_set(&key1 , k1, sizeof(k1));
	dtm_set(&dat1_in , d1+6, sizeof(d1+6));

	if( dtm_replace(&gdbm_fd, &key1, &dat1_in) != 0){
		fprintf(stderr, "%s(%d) replace error %s %s]\n", __FUNCTION__, __LINE__, dtm_getdat(&key1), dtm_getdat(&dat1_in));
	}

	// delete data
	if( dtm_delete(&gdbm_fd, &key2) != 0){
		fprintf(stderr, "%s(%d) delete error key=%s \n", __FUNCTION__, __LINE__, dtm_getdat(&key1));	
	}

	// retrieve data back and print
	dat1_out = dtm_retrieve(&gdbm_fd, &key1);
	fprintf(stdout, "%s(%d) dat1=%s\n", __FUNCTION__, __LINE__, dtm_getdat(&dat1_out));

	fprintf(stdout, "---------------------\r\n");

	gdbm_close(gdbm_fd);

	return 0;
}
