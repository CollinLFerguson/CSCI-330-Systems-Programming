#include "./hw5-scan.h"

int SCAN(FILE *(*stream))
{
    *stream = fopen("hw4.data", "r");
    if(stream==NULL) exit(1);

    int fileLength = 0;
    unsigned char junk;
    while(1)
    {
        junk = fgetc(*stream);
        if(feof(*stream))
        {
            break;
        }

        if(junk == '\n')
        {
            fileLength = fileLength + 1;
        }
    }

    return fileLength;
}
