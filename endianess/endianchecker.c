/**
 * @file endianchecker.c
 * @author Napat Rungruangbangchan
 * @date 7 November 2017 
 * @brief 
 * @Compiler: gcc(ubuntu 14.04)
 * @License: 
 */

#include "endianchecker.h"

bool is_bigendian(){
    int num = 1;
    char *chk = (char *)&num;
    
    if (chk[0] == 1){
        //printf("Little endian\n");
        return 0;   // Little endian 
    }
    else{
        //printf("Big endian\n");
        return 1;   // Big endian 
    }
}
