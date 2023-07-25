#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _JUNK_
#define _JUNK_
struct _data
{
    char *name;
    long number;
};

#endif


struct _data *LOAD(FILE *stream, int size);
