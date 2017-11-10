/**
 *	\file systemcall.h
 *	\brief 
 *  Created on: April 3, 2013
 *  Author: Napat Rungruangbangchan
 */

#ifndef SYSTEMCALL_H_
#define SYSTEMCALL_H_

//! Handling variadic function of system() function
/*!
 \param cmd_va ,The variadic parameter.
 \return shell cmd exit status .[normally: On access return 0, otherwise return number to expect the error].
 */
int system_printf(const char *cmd_va, ...);

//! Handling variadic function of system() function with guarantee sync
/*!
 \param cmd_va ,The variadic parameter.
\return On access return 0, otherwise return number to expect the error.
 */
int system_sync_printf(const char *cmd_va, ...);

//! To check file accessable
/*!
 \param filename , full name with file path.
 \return On access success return 1, otherwise return 0.
 */
int isaccess_file(const char* filename);

//! To check directory accessable
/*!
 \param filename , full name with dir path.
 \return On exist return 1, otherwise return 0 or -1.
 */
int isaccess_dir(const char* filename);

 #endif /* SYSTEMCALL_H_ */
 