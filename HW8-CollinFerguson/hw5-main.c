#include "hw5-main.h"

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
