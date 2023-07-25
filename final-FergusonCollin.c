/*
Collin L. Ferguson
Collin.l.ferguson@und.edu
CSci330
*/

#include <stdio.h>
#include <stdlib.h>

struct myTree{
	float value;
	struct myTree*right, *left;
};
typedef struct myTree NODE;

struct myList{
	NODE *pntNode;
	struct myList *next;
};
typedef struct myList LINK;


LINK *FREE(LINK *head, NODE *root);
LINK *CREATE_LINK(LINK *header, NODE *linkedNode);
NODE *CREATE_NODE(NODE *root, float value); //returns the created node so that it can be more easily linked.
void LOAD(LINK *(*head),NODE *(*root), FILE *stream, int arrayLen);
void PRINT_INORDER(NODE *root);
void PRINT_PREORDER(NODE *root);
void PRINT_POSTORDER(NODE *root);
void PRINT_LIST(LINK *head);
void GET_MIDDLE(float array[], int start, int end, float reordered[]);
void BUBBLE_SORT(float array[], int arrayLen);
int SCAN(FILE *(*stream), char *fileName);


LINK *FREE(LINK *head, NODE *root)
//malloc is only used when the node is created. Since the LL stores the location, I can free everything using it.
{
	LINK *temp = NULL;

	while(head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->pntNode);
		temp->pntNode = NULL;
		free(temp);
	}
	root = NULL;
	return head;
}

void PRINT_INORDER(NODE *root)
{
	if(root == NULL)
	{
		return;
	}

	PRINT_INORDER(root->left);
	printf("%f ", root->value);
	PRINT_INORDER(root->right);
}


void PRINT_PREORDER(NODE *root)
{
	if(root == NULL)
	{
		return;
	}

	printf("%f ", root->value);
	PRINT_PREORDER(root->left);
	PRINT_PREORDER(root->right);
}


void PRINT_POSTORDER(NODE *root)
{
	if(root == NULL)
	{
		return;
	}

	PRINT_POSTORDER(root->left);
	PRINT_POSTORDER(root->right);
	printf("%f ", root->value);
}


void PRINT_LIST(LINK *head)
{
	while(head != NULL)
	{
		printf("%f ", head->pntNode->value);
		head = head->next;
	}
}

void GET_MIDDLE(float array[], int start, int end, float reordered[])
{
	int mid = 0;
	static int cnt = 0;
	mid = (start + end) / 2;
	if (start > end)return;
	reordered[cnt++] = array[mid];
	GET_MIDDLE(array, start, mid-1, reordered);
	GET_MIDDLE(array, mid+1, end, reordered);
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

    return fileLength-1;
}


void BUBBLE_SORT(float array[], int arrayLen)
{
	for(int i = 0; i < arrayLen - 1; i++)
	{
		for(int j = 0; j < arrayLen-i-1; j++)
		{
			if (array[j] > array[j+1])
			{
				int temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
	//return array;
}


void LOAD(LINK *(*head),NODE *(*root), FILE *stream, int arrayLen)
//Reads data from file, then sends read data to CREATE_X functions.
{
	float array[arrayLen];
	float reordered[arrayLen];

	rewind(stream);

	for(int i = 0; i<arrayLen; i++)
	{
		fscanf(stream, "%f", &array[i]);
		//printf("0--%d---\n", array[i]);
	}

	BUBBLE_SORT(array, arrayLen);

	GET_MIDDLE(array, 0, arrayLen, reordered);

	//printf("---CREATE NODES Begin---\n");
	*root = CREATE_NODE(*root, reordered[0]);
	*head = CREATE_LINK(*head, *root);
	NODE *temp = NULL;
	for(int i = 1; i<arrayLen; i++)
	{
		temp = CREATE_NODE(*root, reordered[i]);
		*head = CREATE_LINK(*head, temp);
	}
}


NODE *CREATE_NODE(NODE *root, float value)
//Creates a new node and adds it to the BT. returns the new node.
{
	if(root == NULL)
	{

		NODE *node = NULL;
		node = malloc(sizeof(NODE));
		node->value = value;
		node->left = NULL;
		node->right = NULL;
		return node;
	}

	if(value < root->value)
	{
		if(root->left == NULL)
		{
			NODE *node = NULL;
			node = malloc(sizeof(NODE));
			node->value = value;
			node->left = NULL;
			node->right = NULL;
			root->left = node;
			return node;
		}
		else
		{
			return CREATE_NODE(root->left, value);
		}
	}
	else //(value > root->value)
	{
		if(root->right == NULL)
		{
			NODE *node = NULL;
			node = malloc(sizeof(NODE));
			node->value = value;
			node->left = NULL;
			node->right = NULL;
			root->right = node;
			return node;
		}
		else
		{
			return CREATE_NODE(root->right, value);
		}
	}
}


LINK *CREATE_LINK(LINK *head, NODE *node)
//Creates a new link at the end of the Linked List. Returns head of the list.
{
	LINK *tempLink = NULL;
	tempLink = malloc(sizeof(LINK));
	tempLink->pntNode = node;
	tempLink->next = NULL;

	if(head == NULL)
	{
		head = tempLink;
		return head;
	}

	tempLink->next = head;
	return tempLink;

	/*
	LINK *current = NULL;
	current = head;
	while(current->next !=NULL)
	{
		current = current->next;
	}
	current->next = tempLink;
	*/

	return head;
}


int main(void)
{
	NODE *root = NULL;
	LINK *head = NULL;

	//printf("---LOAD begin---\n");
	FILE *stream;
	int arrayLen = 0;
	arrayLen = SCAN(&stream, "final.data");

	LOAD(&head, &root, stream, arrayLen);

	fclose(stream);

	//printf("---LOAD Successful---\n");

	//printf("---PRINT/FREE Begin---\n");
	printf("in-order:\n");
	PRINT_INORDER(root);
	printf("\n");
	printf("pre-order:\n");
	PRINT_PREORDER(root);
	printf("\n");
	printf("post-order:\n");
	PRINT_POSTORDER(root);
	printf("\n");
	printf("Linked List\n");
	PRINT_LIST(head);
	printf("\n");

	head = FREE(head, root);
	//printf("---PRINT/FREE Successful---\n");

	return 0;

}
