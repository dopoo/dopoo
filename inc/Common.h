#ifndef __DOPOOCOMMON__
#define __DOPOOCOMMON__

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#define __DEBUG__

extern bool print;

static inline void 
dopoo_print(bool isPrint, char *fmt, ...) 
{
	#ifdef __DEBUG__
    va_list va;
    va_start (va, fmt);
    
    if(isPrint)
    {
        vprintf (fmt, va);
    }

    va_end (va);
    #endif
}

#endif