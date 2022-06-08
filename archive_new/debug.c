#include <stdio.h>
#include <stdarg.h>
#include "debug.h"


int debug_print(const char *format,...){
    int ret = 0;
#ifdef DEBUGPR
    va_list args;
    va_start(args, format);
    ret = vprintf(format, args);
    va_end(args);

#endif
    return ret;
}

