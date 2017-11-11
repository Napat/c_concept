/**
 * @file filefolder.h
 * @author Napat Rungruangbangchan
 * @date 12 November 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#ifndef __FILEFOLDER_H__
#define __FILEFOLDER_H__

//! To list file and folder in directory
/*!
 \param dir to list file and folder.
 \return On success return 0, otherwise error.
 */
int lsdir(const char* dir);

//! To list file and folder in directory
/*!
 \param dir to list file and folder.
 \param out_buf buffer to keep output.
 \param lscount list count.  
 \return On success return 0, otherwise error.
 */
int lsdir_buf(const char* dir, char* out_buf, int* lscount);

#endif /* __FILEFOLDER_H__ */
