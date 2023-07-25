/*
Collin L. Ferguson
Collin.l.ferguson@ndus.edu
330 Systems Programming hw11
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct graphNode {
	char name[42]; // Establishment name
	int arcCnt; // Number of outgoing arc from this node
	int weights[10]; // Weights of each outgoing arc from this node
	struct graphNode *arcs[10];
};
typedef struct graphNode graphNode;


struct listNode {
	char name[42];
	struct listNode *next; 		// Establishment name
	graphNode *graph;	// Pointer into graph
};
typedef struct listNode listNode;


void LOAD(char *fileName, graphNode *(*graphHead), listNode *(*listHead));
listNode *FREE(listNode *listHead);

void PRINT_GRAPHNODES(listNode *listHead);
void WALK_PATH(graphNode *graphHead, char destination[]);

graphNode *MAKE_GRAPHNODE(char name[]); //creates a node in graphNode. Returns the node.
graphNode *GRAB_NODE(listNode *listHead, char currentEntry[]); //grabs a node from the graph. useful for the 10 arcs in a row.

listNode *MAKE_LISTNODE(listNode *listHead, graphNode *currentNode, char name[]); //creates a node in listNode. Returns the head.


listNode *FREE(listNode *listHead)
{
	listNode *temp = listHead;
	while(temp!=NULL)
	{
		listHead = listHead->next;
		free(temp->graph);
		free(temp);
		temp = listHead;
	}
	return NULL;
}


void WALK_PATH(graphNode *graphHead, char destination[])
{
	srand(2021);
	int index = 0;
	int total = 0;
	//index = (random() % graphHead->arcCnt);

	graphNode *currentNode = graphHead;
	while(strcmp(currentNode->name, destination))
	{
		index = (random() % currentNode->arcCnt);
		total += currentNode->weights[index];
		currentNode = currentNode->arcs[index];
	}
	printf("Start Node:       %s\nEnd Node:         %s\nAccumulated Cost: %d\n", graphHead->name, currentNode->name, total);
}


void PRINT_GRAPHNODES(listNode *listHead)
{
	listNode *temp = listHead;
	while(temp!= NULL)
	{
		//printf("--%s: %s\n", temp->name, temp->graph->name);

		printf("%s\n", temp->graph->name);
		for(int x=0;x<temp->graph->arcCnt;x++)
		{
			printf("--%s: %d\n", temp->graph->arcs[x]->name, temp->graph->weights[x]);
		}
		temp = temp->next;
	}
}


graphNode *GRAB_NODE(listNode *listHead, char name[])
{
	listNode *temp = listHead;
	while(strcmp(temp->name, name) && temp!=NULL)
	{
		temp=temp->next;
	}
	return temp->graph;
}


listNode *MAKE_LISTNODE(listNode *listHead, graphNode *currentNode, char name[])
{
	//printf("---Make List start\n");
	listNode *temp = malloc(sizeof(listNode));
	strcpy(temp->name, name);
	temp->graph = currentNode;
	temp->next = NULL;

	if(listHead == NULL)
	{
		listHead = temp;
		//printf("---Make List success\n");
		return listHead;
	}

	listNode *listEnd = listHead;

	while(listEnd->next != NULL) {listEnd = listEnd->next;}
	listEnd->next = temp;

	//printf("---Make List success\n");
	return listHead;
}


graphNode *MAKE_GRAPHNODE(char name[])
{
	//printf("---Make Graph start\n");
	graphNode *temp = malloc(sizeof(graphNode));
	strcpy(temp->name, name);
	temp->arcCnt = 0;

	//printf("---Make Graph success\n");
	return temp;
}


void LOAD(char *fileName, graphNode *(*graphHead), listNode *(*listHead))
{
	FILE *stream;
	stream = fopen(fileName, "r");
	if(stream==NULL){printf("File not found"); exit(0);}
	char currentEntry[42]="NULL";

	fscanf(stream, "%s", currentEntry);
	while(strcmp(currentEntry, "STOP")) //Make graphNodes
	{
		//printf("---Make start\n");
		*listHead = MAKE_LISTNODE(*listHead, MAKE_GRAPHNODE(currentEntry), currentEntry);
		//printf("---Make success\n");

		fscanf(stream, "%s", currentEntry);
	}

	char currentDestination[42];

	int destinationWeight = -1;
	graphNode *tempNode=NULL;

	//PRINT_GRAPHNODES(*listHead);

	fscanf(stream, "%s %s %d", currentEntry, currentDestination, &destinationWeight);

	while((strcmp(currentEntry, "STOP")) && (strcmp(currentDestination, "STOP")) && (destinationWeight)) //Filling arcs
	{
		//printf("---%s %s %d\n", currentEntry, currentDestination, destinationWeight);

		//printf("%s %s\n", currentEntry,tempNode->name);

		if(!tempNode || strcmp(currentEntry, tempNode->name))
		{
			tempNode = GRAB_NODE(*listHead, currentEntry);
		}

		tempNode->arcs[tempNode->arcCnt] = GRAB_NODE(*listHead, currentDestination);
		tempNode->weights[tempNode->arcCnt] = destinationWeight;
		tempNode->arcCnt++;

		fscanf(stream, "%s %s %d", currentEntry, currentDestination, &destinationWeight);
	}

	fscanf(stream, "%s", currentEntry);

	*graphHead = GRAB_NODE(*listHead, currentEntry);

	fclose(stream);
}


int main()
{
	graphNode *graphHead=NULL;
	listNode *listHead=NULL;
	//printf("---Load Begin\n");
	LOAD("hw11.data", &graphHead, &listHead);
	//printf("---Load Success\n");
	//printf("---Print Begin\n");
	//PRINT_GRAPHNODES(listHead);
	//printf("---Print Success\n");
	//printf("---Walk Begin\n");
	WALK_PATH(graphHead, "Home");
	//printf("---Walk Success\n");
	//printf("FREE Start\n");
	FREE(listHead);
	//printf("FREE Success\n");

	return 0;
}
