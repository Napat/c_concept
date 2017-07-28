/**
 * @file sgdbm.c
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
#include "gdbmwrapper.h"
#include "sgdbm.h"

/**
 * @brief Open sgdbm file
 * 
 * @return on error return NULL, otherwise return GDBM_FILE fd
 */
GDBM_FILE sgdbm_open(char * db_fname){
	return dtm_open(db_fname);
}

/**
 * @brief Close GDBM_FILE
 * 
 * @return void 
 */
void sgdbm_close(GDBM_FILE gdbm_fd){
	if(gdbm_fd != NULL){
		dtm_close(gdbm_fd);
		gdbm_fd = NULL;
	}
	return;
}

/**
 * @brief insert by key & value
 * 
 * @return negative when error, otherwise return 0
 */
int sgdbm_insert(GDBM_FILE gdbm_fd, char * key, sgdbm_record_t * srec){
	datum key_datum, val_datum;
	dtm_set(&key_datum , key, strlen(key)+1);
	dtm_set(&val_datum, (char*)srec, sizeof(*srec));	

	if( dtm_insert(&gdbm_fd, &key_datum, &val_datum) != 0){
		fprintf(stderr, "%s(%d) insert error, expect key '%s' is already in database\n", __FUNCTION__, __LINE__, dtm_getdat(&key_datum));
		return -1;
	}	
	return 0;
}

/**
 * @brief update by key & value
 * 
 * @return negative when error, otherwise return 0
 */
int sgdbm_update(GDBM_FILE gdbm_fd, char * key, sgdbm_record_t * srec){
	datum key_datum, val_datum;
	dtm_set(&key_datum , key, strlen(key)+1);
	dtm_set(&val_datum, (char*)srec, sizeof(*srec));	

	if( dtm_replace(&gdbm_fd, &key_datum, &val_datum) != 0){
		fprintf(stderr, "%s(%d) update error, expect key '%s' is already in database\n", __FUNCTION__, __LINE__, dtm_getdat(&key_datum));
		return -1;
	}	
	return 0;
}

/**
 * @brief Get record by key
 * 
 * @return sizeof value
 */
int sgdbm_get(GDBM_FILE gdbm_fd, char * key, sgdbm_record_t * srec){
	int len;
	datum key_datum, val_datum;
	dtm_set(&key_datum , key, strlen(key)+1);

	val_datum = dtm_retrieve(&gdbm_fd, &key_datum);
	len = dtm_getdsize(&val_datum);
	memcpy((char *)srec, (char *)dtm_getdat(&val_datum), len);

	return len;
}

/**
 * @brief Delete record by key
 * 
 * @return on success return 0, otherwise error 
 */
int sgdbm_del(GDBM_FILE gdbm_fd, char * key){
	datum key_datum;
	dtm_set(&key_datum , key, strlen(key)+1);

	return dtm_delete(&gdbm_fd, &key_datum);
}

/**
 * @brief Next key
 * 
 * @return next key string, return NULL if end of database
 */
char * sgdbm_key_next(GDBM_FILE gdbm_fd, char * key, datum * pkey_datum_out){	
	if(key[0] == 0){
		// firstkey
		*pkey_datum_out = dtm_key_first(gdbm_fd);

		if(dtm_getdat(pkey_datum_out) == NULL){
			fprintf(stdout, "Database is empty!!\n\n");
			return  NULL;
		}

		strcpy(key, dtm_getdat(pkey_datum_out));
		return key;
	}else{
		// nextkey
		dtm_set(pkey_datum_out , key, strlen(key)+1);	
		*pkey_datum_out = dtm_key_next(gdbm_fd, *pkey_datum_out);
		if(dtm_getdat(pkey_datum_out) == NULL){
			fprintf(stdout, "End of database!!\n\n");
			return  NULL;
		}		
	}
	strcpy(key, dtm_getdat(pkey_datum_out));
	return key;
}
