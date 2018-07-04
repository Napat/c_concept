// https://curl.haxx.se/libcurl/c/sftpget.html
// https://curl.haxx.se/libcurl/c/sftpuploadresume.html

#include <stdio.h>
#include "curl_sftp.h"

int main(void) {
    uint8_t ret;

    // sftp get
    curl_sftp_init();
    ret = curl_sftp_get("sftp://foo:123@10.0.75.1:2222/share/testfile", "./gettofile.bin");
    if(ret != 0){
        printf("Error!! curl_sftp_get: %u\n", ret);
    }

    // sftp put
    ret = curl_sftp_put("sftp://foo:123@10.0.75.1:2222/share/putfile", "./gettofile.bin");
    if(ret != 0) {
        printf("resumed upload using curl %s failed\n", curl_version());
    }

    return 0;
}
