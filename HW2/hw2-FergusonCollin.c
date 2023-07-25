/*
Collin L. Ferguson
Collin.L.Ferguson@und.edu
CSCI 330 Systems Programming
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_LEN 100

struct fileData
{
    char name[31];
    float fltValue;
    int intValue;
    char description[31];

}fileData;

void printHtLArray(struct fileData * dataArray, int arrayLen)
{
    for(int x = 0; x<arrayLen;x++)
    {
        if(strcmp(dataArray[x].name, "\0"))
        {
            printf("%s %f %d %s\n", dataArray[x].name, dataArray[x].fltValue,
                     dataArray[x].intValue, dataArray[x].description);
        }
        else break;
    }
    printf("\n");
    free(dataArray);
}

void printLtHArray(struct fileData * dataArray, int arrayLen)
{
    for(int x = arrayLen - 1; x > -1 ;x--)
    {
        if(strcmp(dataArray[x].name, "\0"))
        {
            printf("%s %f %d %s\n", dataArray[x].name, dataArray[x].fltValue,
                     dataArray[x].intValue, dataArray[x].description);
        }
    }
    printf("\n");
    free(dataArray);
}

struct fileData * floatSlowSort(struct fileData * dataArray, int arrayLen)
{
    for(int i = 0; i < arrayLen; i++)
    {
        if(!strcmp(dataArray[i].name, "\0")){break;}
        for(int j = 0; j < arrayLen-i; j++)
        {
            if(!strcmp(dataArray[j+1].name, "\0")||!strcmp(dataArray[j].name, "\0")){break;}

            if(dataArray[j].fltValue > dataArray[j+1].fltValue)
            {
                struct fileData temp = dataArray[j];
                dataArray[j] = dataArray[j+1];
                dataArray[j+1] = temp;
            }
        }
    }
    return dataArray;
};

struct fileData * intSlowSort(struct fileData * dataArray, int arrayLen)
{
    for(int i = 0; i < arrayLen; i++)
    {
        if(!strcmp(dataArray[i].name, "\0")){break;}
        for(int j = 0; j < arrayLen-i; j++)
        {
            if(!strcmp(dataArray[j+1].name, "\0")||!strcmp(dataArray[j].name, "\0")){break;}

            if(dataArray[j].intValue > dataArray[j+1].intValue)
            {
                struct fileData temp = dataArray[j];
                dataArray[j] = dataArray[j+1];
                dataArray[j+1] = temp;
            }
        }
    }
    return dataArray;
};


struct fileData * loader()
{
    FILE *data;
    data = fopen("hw2.data", "r");

    char first[31];
    char last[31];
    float second = -1.0;
    int third = -1;

    struct fileData *dataArray = calloc(FILE_LEN, sizeof(struct fileData));
    int i = 0;
    while(1)
    {
        fscanf(data, "%s %f %d %s", first, &second, &third, last);
        if(feof(data)){break;}
        strcpy(dataArray[i].name,first);
        dataArray[i].fltValue = second;
        dataArray[i].intValue = third;
        strcpy(dataArray[i].description ,last);
        i++;
    }

    fclose(data);
    return dataArray;
}

void printMenu()
{
    printf("1. Sort data by the float value & print high to low\n");
    printf("2. Sort data by the float value & print low to high\n");
    printf("3. Sort data by the int value & print high to low\n");
    printf("4. Sort data by the int value & print low to high\n");
    printf("5. Exit\n");
}

int main()
{
    int userInput = 0;
    while(1)
    {
        printMenu();
        printf("select an option: ");
        scanf("%d", &userInput);
        if (userInput == 1)
        {
           printHtLArray(floatSlowSort(loader(),FILE_LEN),FILE_LEN);
        }
        else if(userInput == 2)
        {
            printLtHArray(floatSlowSort(loader(),FILE_LEN),FILE_LEN);
        }
        else if(userInput == 3)
        {
            printHtLArray(intSlowSort(loader(),FILE_LEN),FILE_LEN);
        }
        else if(userInput == 4)
        {
            printLtHArray(intSlowSort(loader(),FILE_LEN),FILE_LEN);
        }
        else if(userInput == 5)
        {
           exit(0);
        }

    }

    return 0;
}
