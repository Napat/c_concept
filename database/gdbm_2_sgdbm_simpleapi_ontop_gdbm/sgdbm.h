/**
 * @file sgdbm.h
 * @author Napat Rungruangbangchan
 * @date 27 July 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#ifndef __SGDB_H__
#define __SGDB_H__

#include <gdbm.h>

#define DB_FILENAME		"customers.gdbm"

typedef struct sgdbm_record_s {
	unsigned int id;
	char	firstname[16];
	char	lastname[16];
	char	city[16];
	int 	yearofbirth;
} sgdbm_record_t;

/**
 * @brief Open sgdbm file
 * 
 * @return on error return NULL, otherwise return GDBM_FILE fd
 */
GDBM_FILE sgdbm_open(char * db_fname);

/**
 * @brief Close GDBM_FILE
 * 
 * @return void 
 */
void sgdbm_close(GDBM_FILE gdbm_fd);

/**
 * @brief insert by key & value
 * 
 * @return negative when error, otherwise return 0
 */
int sgdbm_insert(GDBM_FILE gdbm_fd, char * key, sgdbm_record_t * srec);

/**
 * @brief update by key & value
 * 
 * @return negative when error, otherwise return 0
 */
int sgdbm_update(GDBM_FILE gdbm_fd, char * key, sgdbm_record_t * srec);

/**
 * @brief Get record by key
 * 
 * @return sizeof value
 */
int sgdbm_get(GDBM_FILE gdbm_fd, char * key, sgdbm_record_t * srec);

/**
 * @brief Delete record by key
 * 
 * @return on success return 0, otherwise error 
 */
int sgdbm_del(GDBM_FILE gdbm_fd, char * key);

/**
 * @brief Next key
 * 
 * @return next key string, return NULL if end of database
 */
char * sgdbm_key_next(GDBM_FILE gdbm_fd, char * key, datum * pkey_datum_out);

#endif /* __SGDB_H__ */
