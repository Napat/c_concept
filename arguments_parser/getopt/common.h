#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define DEBUG

#define IP4_MAXLEN          (16)
#define USER_MAXLEN         (20)
#define PASSWD_MAXLEN       (256)

typedef struct input_args_s 
{   
    int verbose_flag;
    char filepath[FILENAME_MAX];
    char ip_address[IP4_MAXLEN];
    int32_t port;
    char user[USER_MAXLEN];
    char pass[PASSWD_MAXLEN];
} input_args_t;

FILE* debug_info();
FILE* debug_error();

#endif /* __COMMON_H__ */
