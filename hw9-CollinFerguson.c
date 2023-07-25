/*
 Collin L. Ferguson
 Collin.l.ferguson@und.edu
 CSci 330: hw9
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node{
	char *word;
	struct node *next;
};
typedef struct node _NODE;


struct codex{
	char *word1;
	char *word2;
	struct codex *next;
};
typedef struct codex _CONODE;


_NODE *newNODE(char *word);

_NODE *createNODELL(_NODE *nodeHead, char *word);
_CONODE *createCONODELL(_CONODE *conodeHead, char *word1, char *word2);

_NODE *freeNODE(_NODE *nodeHead);
_CONODE *freeCONODE(_CONODE *head);

void LOAD(FILE *data, FILE *codex, _NODE *(*nodeHead), _CONODE *(*conodeHead)); // takes both files and both list heads

void printNODE(_NODE *nodeHead);
void printCONODE(_CONODE *conodeHead);

void printFinal(_NODE *nodeHead);

_NODE *correctNODE(_NODE *nodeHead, _CONODE *conodeHead);


void printFinal(_NODE *nodeHead)
{
	_NODE *tempNode = nodeHead;
	while(tempNode != NULL)
	{
		if(!strcmp(tempNode->next->word, ",") || !strcmp(tempNode->next->word, "." ))
		{
			printf("%s%s\n",tempNode->word, tempNode->next->word);
			tempNode = tempNode->next->next;
		}
		else
		{
			printf("%s ", tempNode->word);
			tempNode = tempNode->next;
		}
	}
}


_NODE *correctNODE(_NODE *nodeHead, _CONODE *conodeHead)
{
	_NODE *tempNode = nodeHead;
	_CONODE *tempConode = conodeHead;
	int boolFound = 0;

	while (tempNode->next!=NULL) // // // Deals with everything but the head node.
	{
		boolFound = 0;
		while(tempConode!=NULL && boolFound < 1)
		{
			if(!strcmp(tempConode->word1,tempNode->next->word))
			{
				//printf("---Match found:%s -> %s, %s \n",tempConode->word1, tempConode->word2,tempNode->next->word);

				if(!strcmp(tempConode->word2, "skip"))
				{
					//Delete node
					//printf("---Delete Start\n");
					_NODE *trashNode = tempNode->next;
					tempNode->next = tempNode->next->next;
					free(trashNode->word); free(trashNode);
					//printf("---Delete Success\n");
				}
				else
				{
					//change word
					//printf("---Change Start\n");
					/*//REALLOC method of doing this.
					tempNode->next->word = realloc(tempNode->next->word, strlen(tempConode->word2)); //reallocates the memory to the new size.
					strcpy(tempNode->next->word, tempConode->word2);			//man pages say the original ptr is freed automatically by realloc().
					*/

					_NODE *newNode = newNODE(tempConode->word2);
					newNode->next = tempNode->next->next;
					free(tempNode->next->word);
					free(tempNode->next);
					tempNode->next = newNode;

					//printf("---Change Complete\n");
				}

				boolFound++;
			}
			tempConode = tempConode->next;
		}
		tempNode = tempNode->next;
		tempConode = conodeHead;
	}

	tempNode = nodeHead;
	boolFound = 0;
	while(tempConode!=NULL && boolFound < 1) // // // Deals with the head node.
	{
		if(!strcmp(tempConode->word1,tempNode->word))
		{
			//printf("---Match found:%s -> %s, %s \n",tempConode->word1, tempConode->word2,tempNode->word);

			if(!strcmp(tempConode->word2, "skip"))
			{
				//Delete node
				//printf("---Delete Start\n");
				nodeHead = nodeHead->next;
				free(tempNode->word); free(tempNode);
				//printf("---Delete Success\n");
			}
			else
			{
				//change word
				//printf("---Change Start\n");
				/*
				tempNode->word = realloc(tempNode->word, strlen(tempConode->word2)); //reallocates the memory to the new size.
				strcpy(tempNode->word, tempConode->word2);			//man pages say the original ptr is freed automatically by realloc().
				*/

				_NODE *newNode = newNODE(tempConode->word2);
				newNode->next = nodeHead->next;
				free(nodeHead->word);
				free(nodeHead);
				nodeHead = newNode;
				//printf("---Change Complete\n");
			}

			boolFound++;
		}
		tempConode = tempConode->next;
	}
	return nodeHead;
}


_CONODE *createCONODELL(_CONODE *conodeHead, char *word1, char *word2)
{
	_CONODE *newNode = malloc(sizeof(_CONODE));
	newNode->word1 = malloc(strlen(word1)+1);
	newNode->word2 = malloc(strlen(word2)+1);
	strcpy(newNode->word1, word1);
	strcpy(newNode->word2, word2);
	newNode->next = NULL;

	if(conodeHead == NULL)
	{
		conodeHead = newNode;
		return conodeHead;
	}

	_CONODE *temp = conodeHead;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newNode;
		return conodeHead;
}


_CONODE *freeCONODE(_CONODE *nodeHead)
{
	_CONODE *temp = nodeHead;
	while (temp != NULL)
	{
		nodeHead = nodeHead->next;
		free(temp->word1);
		temp->word1 = NULL;
		free(temp->word2);
		temp->word2 = NULL;
		free(temp);
		temp = nodeHead;
	}
	return nodeHead;
}


void printCONODE(_CONODE *conodeHead)
{
	_CONODE *temp = conodeHead;
	while(temp!=NULL)
	{
		printf("%s -> %s\n",temp->word1, temp->word2);
		temp = temp->next;
	}
}


_NODE *newNODE(char *word) //Creates and returns a new node
{ //It's own function so it can be utilized in correctNode() when the previous node needs replaced.
	_NODE *newNode = malloc(sizeof(_NODE));
		newNode->word = malloc(strlen(word)+1);
		strcpy(newNode->word, word);
		newNode->next = NULL;
		return newNode;
}

_NODE *createNODELL(_NODE *nodeHead, char *word)
{
	_NODE *newNode = newNODE(word);
	
	//printf("---%s\n",newNode->word);

	if(nodeHead == NULL)
	{
		nodeHead = newNode;
		return nodeHead;
	}
	
	_NODE *temp = nodeHead;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newNode;
	return nodeHead;
}


void printNODE(_NODE *nodeHead)
{
	_NODE *temp = nodeHead;
	while(temp!=NULL)
	{
		printf("%s\n",temp->word);
		temp = temp->next;
	}
}


_NODE *freeNODE(_NODE *nodeHead)
{
	_NODE *temp = nodeHead;
	while (temp != NULL)
	{
		nodeHead = nodeHead->next;
		free(temp->word);
		temp->word = NULL;
		free(temp);
		temp = nodeHead;
	}
	return nodeHead;
}


void LOAD(FILE *data, FILE *codex, _NODE *(*nodeHead), _CONODE *(*conodeHead))
{
	char *line = NULL;
	char *temp = NULL;
	size_t junk = 0;

	//Filling the data LL>
	char punctuation[2] = " ";

	getline(&line, &junk, data);
	while(!feof(data))
	{
		char *index = line;

		//finds the punctuation at the end of line.
		while(*index != '\0')
		{
			if(*index == ',' || *index == '.'){punctuation[0]=*index;}
			index++;
		}
		//printf("---Punctuation:%s\n", punctuation);

		//create nodes by taking out words.
		temp = strtok(line, " ,.\n");
		while(temp != NULL)
		{
			//printf("---Create Node: %s\n", temp);
			//printf("---Create Node Begin\n");
			*nodeHead = createNODELL(*nodeHead, temp);
			//printf("---Create Node Successful\n");
			temp = strtok(NULL, " ,.\n"); //strtok has multiple delimiters. punctuation was pulled out at the start.
		}
		*nodeHead = createNODELL(*nodeHead, punctuation);
		getline(&line, &junk, data);
	}

	temp = NULL;
	//Filling the codex LL>
	getline(&line, &junk, codex);
	while(!feof(codex))
	{
		temp = strtok(line, " ");
		char *word1 = malloc(strlen(temp)); //This block could create errors.
		strcpy(word1, temp);
		temp = strtok(NULL, " \n\0");
		char *word2 = malloc(strlen(temp));
		strcpy(word2, temp);
		//printf("---Create CoNode Begin\n"); /*: %s %s\n", word1, word2);*/
		*conodeHead	= createCONODELL(*conodeHead, word1, word2);
		//printf("---Create CoNode Successful\n");
		free(word1); free(word2);
		getline(&line, &junk, codex);
	}
	free(line);
}


int main()
{
	FILE *data = fopen("hw9data.txt", "r");
	if (data == NULL){printf("file could not be found"); exit(-1);}
	FILE *codex = fopen("hw9codex.txt", "r");
	if (codex == NULL){printf("file could not be found"); exit(-1);}

	_NODE *nodeHead = NULL;
	_CONODE *conodeHead = NULL;
	//printf("---LOAD Start\n");
	LOAD(data, codex, &nodeHead, &conodeHead);
	fclose(data);
	fclose(codex);
	//printf("---LOAD Success\n");

	//printNODE(nodeHead);
	//printCONODE(conodeHead);

	//printf("---Correct Start\n");
	nodeHead = correctNODE(nodeHead, conodeHead);
	//printNODE(nodeHead);
	//printf("---Correct Success\n");

	printFinal(nodeHead);

	//printf("---Free Start\n");
	nodeHead = freeNODE(nodeHead);
	conodeHead = freeCONODE(conodeHead);
	//printf("---Free Success\n");

	return 0;
}

