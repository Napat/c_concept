/**
 * @file main.c
 * @author Napat Rungruangbangchan
 * @date 4 July 2018 
 * @brief Example use of curl_sftp.c/h
 * @Compiler: gcc(Ubuntu 16.04.4 LTS)
 * @License: 
 */

#include <stdio.h>
#include <stdlib.h>
#include "curl_sftp.h"

void prepare_test_get_resume(char *filename, int byte_num_to_remove_from_file) {
    char filename2[255];
    char cmd[255];

    sprintf(filename2, "%s_2", filename);
    
    sprintf(cmd, "cp %s %s", filename, filename2);
    system(cmd);

    // remove x chars from the end of file
    sprintf(cmd, "truncate -s-%d %s", byte_num_to_remove_from_file, filename2);    // truncate -s-1 file
    system(cmd);

    sprintf(cmd, "cat %s", filename2);
    system(cmd);
    printf("\n");
}

int main(void) {
    uint8_t ret;

    // init global curl
    curl_sftp_init();

    // sftp get
    ret = curl_sftp_get("sftp://foo:123@127.0.0.1:2222/share/testfile", "./gettofile.bin");
    if(ret != 0){
        printf("Error!! curl_sftp_get: %u\n", ret);
    }

    // sftp put
    ret = curl_sftp_put("sftp://foo:123@127.0.0.1:2222/share/putfile", "./gettofile.bin");
    if(ret != 0) {
        printf("resumed upload using curl %s failed\n", curl_version());
    }

    // prepare file for testing get_resume() 
    prepare_test_get_resume("./gettofile.bin", 3);

    // sftp get_resume
    ret = curl_sftp_get_resume("sftp://foo:123@127.0.0.1:2222/share/testfile", "./gettofile.bin_2");
    if(ret != 0){
        printf("Error!! curl_sftp_get: %u\n", ret);
    }

    return 0;
}
