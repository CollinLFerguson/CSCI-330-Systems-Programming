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

void SEARCH(struct _data *BlackBox, char *name, int size);
