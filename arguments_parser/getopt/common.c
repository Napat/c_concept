#include "common.h"

FILE* debug_info()
{
    static FILE* debug = NULL;
    
    if(debug == NULL)
    {
        #ifdef DEBUG
            return debug = stdout;        
        #else
            return debug = fopen("/dev/null", "w");
        #endif
    }
    return debug;
}

FILE* debug_error()
{
    static FILE* debug = NULL;
    
    if(debug == NULL)
    {
        #ifdef DEBUG
            return debug = stderr;
        #else
            return debug = stderr;
        #endif
    }
    return debug;
}
