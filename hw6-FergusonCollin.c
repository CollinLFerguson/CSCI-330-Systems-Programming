/*
Collin L. Ferguson
Collin.l.ferguson@und.edu
CSci 330
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node{
	char *name;
	struct node *next;
};
typedef struct node LINK;


void LIST_DELETE(char *name, LINK *(*head))
{
	if(strcmp(name, (*head)->name) == 0)
	{
		*head = (*head)->next;
		return;
	}

	LINK *current = NULL;
	current = *head;

	while(current->next != NULL)
	{
		if(strcmp(current->next->name, name) == 0)
		{
			LINK *temp = current->next;
			current->next = temp->next;
			free(temp->name);
			free(temp);
			return;
		}
		current = current->next;
	}
}


LINK *LIST_INSERT(char *name, LINK *head)
{
	//NODE CREATION//
	LINK *tempNode = NULL;
	tempNode = malloc(sizeof(LINK));
	tempNode->name = calloc(strlen(name) + 1, sizeof(char)); //+1 for \0
	strcpy(tempNode->name, name);
	tempNode->next = NULL;
	//NODE CREATION//

	if(head == NULL) // Makes
	{
		return tempNode;
	}

	LINK *current = NULL;
	current = head;

	//INSERTION SORT//
	//printf("---%s / %s---\n",tempNode->name, head->name);
	if(strcmp(tempNode->name, head->name) < 0)
	{
		tempNode->next = head;
		return tempNode;
	}

	while(current->next != NULL)
	{
		//printf("---%s / %s---\n",tempNode->name, current->next->name);
		if(strcmp(tempNode->name, current->next->name) < 0)
		{
			tempNode->next = current->next;
			current->next = tempNode;
			return head;
		}
		current = current->next;
	}
	current->next = tempNode;
	//INSERTION SORT//

	return head;
}


int LIST_SEARCH(char *name, LINK *head)
{
	LINK *current = NULL;
	current = head;

	while(current!=NULL)
	{
		//printf("%d %s, %s\n", strcmp(current->name , name), current->name, name);
		if(strcmp(current->name , name) == 0)
		{
			return 1;
		}
		current=current->next;
	}

	return 0;
}


int SCAN(FILE *(*stream), char *fileName)
{
    *stream = fopen(fileName, "r");
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


void LIST_DISPLAY(LINK *head)
{
	if(head == NULL)
	{
		return;
	}
	LINK *temp = head;
	while(temp != NULL)
	{
		//printf("-X-\n");
		printf("%s\n", temp->name);
		temp = temp->next;

	}
}


LINK *LIST_FREE(LINK *head)
{

	LINK *temp = NULL;

	while(head != NULL)
	{

		temp = head;

		head = head->next;

		free(temp->name);

		free(temp);

	}
	return head;
}


int main(int argv, char**argc)
{
	if(argv < 2)
	{
		printf("********************************************\n");
		printf("* You must include a filename to load.     *\n");
		printf("********************************************\n");
		return 0;
	}

	LINK *head = NULL;

	//printf("--Begin Load--\n");
	// ------BEGIN LOAD------  //
	FILE *stream;
	int size = SCAN(&stream, argc[1]);

	rewind(stream);
	char *line;
	char *temp;
	char *name;

	size_t junk = 0; //used to get the size_t of getline. buffer size is always 120.

	int x = 1;
	while(x < size)
	{
		getline(&line, &junk, stream);

		temp = strtok(line, " ");
		//printf("--%s--\n", temp);
		name = calloc(strlen(temp), sizeof(char));
		strcpy(name, temp);

		temp = strtok(NULL, "\n");

		if(LIST_SEARCH(name, head))
		{
			if(!strcmp(temp,"d"))
					{
						//printf("--Begin Delete--\n");
						LIST_DELETE(name, &head);
						//printf("--End Delete--\n");
					}
		} else
		{
			if(!strcmp(temp,"a"))
			{
				//printf("--Begin Insert--\n");
				head = LIST_INSERT(name, head);
				//printf("--End Insert--\n");
			}
		}


		//LIST_DISPLAY(head);
		//printf("\n\n");
		x++;
	}
	free(line);
	fclose(stream);
	// ------END LOAD------  //

	//printf("--End Load--\n");

	LIST_DISPLAY(head);
	//printf("--End Display--\n");

	LIST_FREE(head);
	//printf("--End Free--\n");

	return 0;
}
