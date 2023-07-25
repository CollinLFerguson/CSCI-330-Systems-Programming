#include <dlfcn.h>
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

	int (*SCAN)(FILE *(*));
	void *handle;

	handle = dlopen("./hw8-lib-CollinFerguson.so", RTLD_LAZY);
	if(!handle){printf("error:%s\n", dlerror());}
	SCAN = dlsym(handle, "SCAN");

	FILE *stream;

	int lines = (*SCAN)(&stream);
	//int lines = SCAN(&stream);
    struct _data *(*LOAD)(FILE *, int);
    LOAD = dlsym(handle, "LOAD");


    struct _data *BlackBox;


    BlackBox = LOAD(stream, lines);

    //printBlackBox(BlackBox, lines);

    void (*SEARCH)(struct _data *, char *, int);
    SEARCH = dlsym(handle, "SEARCH");
    SEARCH(BlackBox, argc[1], lines);


    void (*FREE)(struct _data *, int);
	FREE = dlsym(handle, "FREE");
    FREE(BlackBox, lines);

    dlclose(handle);
    return 0;
}
