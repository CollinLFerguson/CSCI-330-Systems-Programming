#include "./hw5-free.h"

void FREE(struct _data *BlackBox, int size)
{
    for(int i=0; i < size; i++)
    {

    	free(BlackBox[i].name);
    }

    free(BlackBox);
    //printf("--Free successful--\n");
}
