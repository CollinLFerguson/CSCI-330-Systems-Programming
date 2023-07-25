/*
Collin L. Ferguson
collin.l.ferguson@und.edu
CSci 330
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _data
{
    char *name;
    long number;
};


void printBlackBox(struct _data *BlackBox, int size)
//Testing utility function
{
	for(int i=0; i < size; i++)
	{
		printf("--%s %ld--\n", BlackBox[i].name, BlackBox[i].number);
	}

}


void FREE(struct _data *BlackBox, int size)
{
    for(int i=0; i < size; i++)
    {

    	free(BlackBox[i].name);
    }

    free(BlackBox);
    //printf("--Free successful--\n");
}

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


struct _data *LOAD(FILE *stream, int size)
{
    struct _data *BlackBox;
    BlackBox = calloc(size, sizeof(struct _data));

    rewind(stream);
    char *line;
    char *temp;

    size_t junk = 0; //used to get the size_t of getline. buffer size is always 120.

    int x = 0;

    while(x < size)
    {
        getline(&line, &junk, stream);

        temp = strtok(line, " ");

        BlackBox[x].name = calloc(strlen(temp), sizeof(char)); //Could also use malloc(strlen(temp)),
        														//I don't think it matters.
        strcpy(BlackBox[x].name, temp);

        temp = strtok(NULL, "\n");
        BlackBox[x].number = atol(temp);
        x++;
    }
    free(line);

    fclose(stream);

    return BlackBox;
}


void SEARCH(struct _data *BlackBox, char *name, int size)
{
	int bolNameFound = 0;
	for(int i = 0; i < size;i++ )
	{
		//printf("--%s - %s--\n", BlackBox[i].name, name);
		if(strcmp(BlackBox[i].name, name) == 0)
		{
			printf("******************************************\n");
			printf("*   The name was found at the %d entry   *\n", i);
			printf("******************************************\n");
			bolNameFound++;
		}
	}
	if(!bolNameFound)
	{
		printf("******************************************\n");
		printf("*        The name was not found.         *\n");
		printf("******************************************\n");
	}
}


int main(int argv, char **argc)
{
	//printf("--%s--\n", argc[1]);
	//printf("--%d--\n", argv);

	if(argv < 2)
	{
		printf("******************************************\n");
		printf("* You must include a name to search for. *\n");
		printf("******************************************\n");
		exit(0);
	}

	FILE *stream;
    int lines = SCAN(&stream);
    struct _data *BlackBox;

    BlackBox = LOAD(stream, lines);

    //printBlackBox(BlackBox, lines);

    SEARCH(BlackBox, argc[1], lines);

    FREE(BlackBox, lines);

    return 0;
}

