#include "./hw5-load.h"

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
