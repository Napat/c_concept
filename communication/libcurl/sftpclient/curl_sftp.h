/**
 * @file curl_sftp.h
 * @author Napat Rungruangbangchan
 * @date 4 July 2018 
 * @brief 
 * @Compiler: gcc(Ubuntu 16.04.4 LTS)
 * @License: 
 */

#ifndef __CURL_SFTP_H__
#define __CURL_SFTP_H__

#include <stdint.h>
#include <curl/curl.h>

#define IS_CURLVERBOSE  (0L)       // 0L: disable, 1L: enable

struct sftpfile_s
{
    const char *filename;
    FILE *stream;
};

void curl_sftp_init(void);
int8_t curl_sftp_get(char *getfrom_sftpurl, char *getto_fullname);
int8_t curl_sftp_put(const char *remotepath, const char *localpath);
#endif /* __CURL_SFTP_H__ */
