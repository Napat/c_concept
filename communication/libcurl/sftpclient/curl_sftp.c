/**
 * @file curl_sftp.c
 * @author Napat Rungruangbangchan
 * @date 4 July 2018 
 * @brief 
 * @Compiler: gcc(Ubuntu 16.04.4 LTS)
 * @License: 
 */

#include "curl_sftp.h"
#include <sys/stat.h>

static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream) {
    struct sftpfile_s *out = (struct sftpfile_s *)stream;
    if (out && !out->stream) {
        // open file for writing
        out->stream = fopen(out->filename, "wb");
        if (!out->stream)
            return -1; // failure, can't open file to write
    }
    return fwrite(buffer, size, nmemb, out->stream);
}

static size_t my_fwrite_append(void *buffer, size_t size, size_t nmemb, void *stream) {
    struct sftpfile_s *out = (struct sftpfile_s *)stream;
    if (out && !out->stream) {
        // open file for writing
        out->stream = fopen(out->filename, "ab");
        if (!out->stream)
            return -1; // failure, can't open file to write
    }
    return fwrite(buffer, size, nmemb, out->stream);
}

/*
 * sftp_get_remote_filesize returns the remote file size in byte; -1 on error
 */ 
static curl_off_t sftp_get_remote_filesize(const char *i_remoteFile) {
    CURLcode result = CURLE_GOT_NOTHING;
    curl_off_t remoteFileSizeByte = -1;
    CURL *curlHandlePtr = NULL;

    curlHandlePtr = curl_easy_init();
    curl_easy_setopt(curlHandlePtr, CURLOPT_VERBOSE, IS_CURLVERBOSE);

    curl_easy_setopt(curlHandlePtr, CURLOPT_URL, i_remoteFile);
    curl_easy_setopt(curlHandlePtr, CURLOPT_NOPROGRESS, 1);
    curl_easy_setopt(curlHandlePtr, CURLOPT_NOBODY, 1);
    curl_easy_setopt(curlHandlePtr, CURLOPT_HEADER, 1);
    curl_easy_setopt(curlHandlePtr, CURLOPT_FILETIME, 1);

    curl_easy_setopt(curlHandlePtr, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_ANY);

    result = curl_easy_perform(curlHandlePtr);
    
    if(CURLE_OK == result) {
        result = curl_easy_getinfo(curlHandlePtr, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &remoteFileSizeByte);
        //printf("filesize: %" CURL_FORMAT_CURL_OFF_T "\n", remoteFileSizeByte);
    }
    curl_easy_cleanup(curlHandlePtr);

    return remoteFileSizeByte;
}

/*
 * local_filesize_fseek returns the local file size in byte; -1 on error
 */ 
static long local_filesize_fseek(const char *filename)
{
    FILE *fp = NULL;
    long off;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("failed to fopen %s\n", filename);
        return -1;
    }

    if (fseek(fp, 0, SEEK_END) == -1)
    {
        printf("failed to fseek %s\n", filename);
        return -1;
    }

    off = ftell(fp);
    if (off == -1L)
    {
        printf("failed to ftell %s\n", filename);
        return -1;
    }

    if (fclose(fp) != 0)
    {
        printf("failed to fclose %s\n", filename);
        return -1;
    }
    return off;
}

/*
 * readfunc On demand function for libcurl to read local file.
 */
static size_t readfunc(void *ptr, size_t size, size_t nmemb, void *stream) {
    FILE *f = (FILE *)stream;
    size_t n;

    if(ferror(f)) {
        return CURL_READFUNC_ABORT;
    }

    n = fread(ptr, size, nmemb, f) * size;

    return n;
}

/*
 * curl_sftp_init one time init global curl
 */
void curl_sftp_init() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

/*
 * curl_sftp_get get file from remote sftp. 
 * Return 0 if success.
 */ 
int8_t curl_sftp_get(char* getfrom_sftpurl, char* getto_fullname) {
    CURL *curl;
    CURLcode res;
    
    //struct sftpfile_s ftpfile = {"gettofile.bin", NULL};
    struct sftpfile_s ftpfile = {getto_fullname, NULL};

    curl = curl_easy_init();
    if (curl == 0) {
        // curl error
        return -1;
    }

    // Switch on full protocol/debug output
    curl_easy_setopt(curl, CURLOPT_VERBOSE, IS_CURLVERBOSE);

    // ex getfrom_sftpurl: "sftp://foo:123@192.168.43.230:2222/share/testfile"
    curl_easy_setopt(curl, CURLOPT_URL, getfrom_sftpurl);

    // Define our callback to get called when there's data to be written
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    // Set a pointer to our struct to pass to the callback
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);

    // set desired auth types to let libcurl pick a suitable one: https://curl.haxx.se/libcurl/c/CURLOPT_SSH_AUTH_TYPES.html
    curl_easy_setopt(curl, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_ANY);

    res = curl_easy_perform(curl);

    // always cleanup
    curl_easy_cleanup(curl);

    if (CURLE_OK != res) {
        // we failed
        fprintf(stderr, "%s(%d) curl told us %d\n", __FUNCTION__, __LINE__, res);
        return -2;
    }    

    if (ftpfile.stream) {
        fclose(ftpfile.stream);
        ftpfile.stream = NULL;
    }

    curl_global_cleanup();

    return 0;
}

/*
 * curl_sftp_get get file from remote sftp. If local file is avaliable then download and append to the end of file.
 * Return 0 if success.
 */
int8_t curl_sftp_get_resume(char* getfrom_sftpurl, char* getto_fullname) {
    CURL *curl;
    CURLcode res;

    curl_off_t remotefilesizebyte;
    curl_off_t localfilesizebyte;

    // ex: ftpfile = {"gettofile.bin", NULL};
    struct sftpfile_s ftpfile = {getto_fullname, NULL};

    curl = curl_easy_init();
    if (curl == 0) {
        // curl error
        return -1;
    }

    // Switch on full protocol/debug output
    curl_easy_setopt(curl, CURLOPT_VERBOSE, IS_CURLVERBOSE);

    //curl_easy_setopt(curl, CURLOPT_URL, "sftp://foo:123@192.168.43.230:2222/share/testfile");
    curl_easy_setopt(curl, CURLOPT_URL, getfrom_sftpurl);

    // Define our callback to get called when there's data to be written
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite_append);
    // Set a pointer to our struct to pass to the callback
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);

    // set desired auth types to let libcurl pick a suitable one: https://curl.haxx.se/libcurl/c/CURLOPT_SSH_AUTH_TYPES.html
    curl_easy_setopt(curl, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_ANY);

    remotefilesizebyte = sftp_get_remote_filesize(getfrom_sftpurl);
    if(-1 == remotefilesizebyte) {
        //printf("Expect file not found or feature not support, unable to resume upload\n");
        // upload from the begining of file
        remotefilesizebyte = 0;
    }

    //fprintf(stdout, "remotefilesizebyte: %ld\n", remotefilesizebyte);

    localfilesizebyte = local_filesize_fseek(getto_fullname);
    if(localfilesizebyte < 0) {
        localfilesizebyte = 0;
    }
    //fprintf(stdout, "localfilesizebyte: %ld\n", localfilesizebyte);

    if (remotefilesizebyte > localfilesizebyte) {
        if(remotefilesizebyte < 2000000000) {
            curl_easy_setopt(curl, CURLOPT_RESUME_FROM, localfilesizebyte);
        } else {
            curl_easy_setopt(curl, CURLOPT_RESUME_FROM_LARGE, localfilesizebyte);
        }
    } else {
        fprintf(stdout, "No resume lsize/rsize: %ld/%ld\n", localfilesizebyte, remotefilesizebyte);
        return 1;
    }

    res = curl_easy_perform(curl);

    // always cleanup
    curl_easy_cleanup(curl);

    if (CURLE_OK != res) {
        // we failed
        fprintf(stderr, "%s(%d) curl told us %d\n", __FUNCTION__, __LINE__, res);
        return -2;
    }    

    if (ftpfile.stream) {
        fclose(ftpfile.stream);
        ftpfile.stream = NULL;
    }

    curl_global_cleanup();

    return 0;
}

/*
 * curl_sftp_put put file to sftp. Auto resume upload if remote file is avaliable then append to the end of file.
 * Return 0 if success.
 */
int8_t curl_sftp_put(const char *remotepath, const char *localpath) {
    FILE *f = NULL;
    CURLcode result = CURLE_GOT_NOTHING;
    CURL *curlhandle = NULL;    

    curl_off_t remotefilesizebyte;

    remotefilesizebyte = sftp_get_remote_filesize(remotepath);
    if(-1 == remotefilesizebyte) {
        //printf("Expect file not found or feature not support, unable to resume upload\n");
        // upload from the begining of file
        remotefilesizebyte = 0;
    }

    f = fopen(localpath, "rb");
    if(!f) {
        perror(NULL);
        return -2;
    }

    curlhandle = curl_easy_init();

    curl_easy_setopt(curlhandle, CURLOPT_VERBOSE, IS_CURLVERBOSE);
    curl_easy_setopt(curlhandle, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curlhandle, CURLOPT_URL, remotepath);
    curl_easy_setopt(curlhandle, CURLOPT_READFUNCTION, readfunc);
    curl_easy_setopt(curlhandle, CURLOPT_READDATA, f);

    curl_easy_setopt(curlhandle, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_ANY);

#ifdef _WIN32
    _fseeki64(f, remotefilesizebyte, SEEK_SET);
#else
    fseek(f, (long)remotefilesizebyte, SEEK_SET);
#endif
    curl_easy_setopt(curlhandle, CURLOPT_APPEND, 1L);
    result = curl_easy_perform(curlhandle);

    curl_easy_cleanup(curlhandle);
    fclose(f);    

    if(result != CURLE_OK) {
        fprintf(stderr, "%s\n", curl_easy_strerror(result));
        return 3;
    }
        
    return 0;
}
