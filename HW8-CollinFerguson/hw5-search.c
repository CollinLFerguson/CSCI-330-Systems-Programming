#include "./hw5-search.h"

void SEARCH(struct _data *BlackBox, char *name, int size)
{
	int bolNameFound = 0;
	for(int i = 0; i < size;i++ )
	{
		//printf("--%s - %s--\n", BlackBox[i].name, name);
		if(strcmp(BlackBox[i].name, name) == 0)
		{
			printf("******************************************\n");
			printf("The name was found at the %d entry\n", i);
			printf("******************************************\n");
			bolNameFound++;
		}
	}
	if(!bolNameFound)
	{
		printf("******************************************\n");
		printf("The name was not found.\n");
		printf("******************************************\n");
	}
}
