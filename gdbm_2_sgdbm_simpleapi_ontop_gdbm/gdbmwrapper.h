/**
 * @file gdbmwrapper.h
 * @author Napat Rungruangbangchan
 * @date 22 July 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#ifndef __GDBWRAPPER_H__
#define __GDBWRAPPER_H__

#include <gdbm.h>

/**
 * @brief open gdbm
 * 
 * @return on error return NULL, otherwise return GDBM_FILE fd
 */
GDBM_FILE dtm_open(char * db_fname);

/**
 * @brief close gdbm
 * 
 * @return void
 */
void dtm_close(GDBM_FILE gdbm_fd);

/**
 * @brief To prepare key or data to be insert to gdbm
 * 
 * @return on success return 0, otherwise error
 */
int dtm_set(datum * dtm, char * dat, int size);

/**
 * @brief To get value(data and size) from datum type
 * 
 * @return on success return 0, otherwise error
 */
int dtm_get(datum * dtm, char * dat, int size);

/**
 * @brief To get value(data) from datum type
 * 
 * @return data
 */
char * dtm_getdat(datum * dtm);

/**
 * @brief To get value(size) from datum type
 * 
 * @return size
 */
int dtm_getdsize(datum * dtm);

/**
 * @brief To insert new key with data
 * Only insert data if key is not available in database
 * 
 * @return on success return 0, otherwise error
 */
int dtm_insert(GDBM_FILE * gdbm_fd, datum * key, datum * dat);

/**
 * @brief To replace data if key exist
 * 
 * @return on success return 0, otherwise error
 */
int dtm_replace(GDBM_FILE * gdbm_fd, datum * key, datum * dat);

// Retrieve data by key
/**
 * @brief Retrieve data by key
 * Get data by key
 * 
 * @return data on success
 */
datum dtm_retrieve(GDBM_FILE * gdbm_fd, datum * key);

/**
 * @brief To delete data by key
 *
 * @return on success return 0, otherwise error
 */
int dtm_delete(GDBM_FILE * gdbm_fd, datum * key);


#endif /* __GDBWRAPPER_H__ */
