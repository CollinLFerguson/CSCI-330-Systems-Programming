/*
Collin L. Ferguson
Collin.l.ferguson@und.edu
CSci 330: homework 10
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char uchar;

uchar *PGM_FILE_READ_1D(char *FileName, int *Width, int *Height, int *color);
void PGM_FILE_WRITE_1D(char *FileName, uchar *Image, int Width, int Height, int color);
void pgmCommentClear(FILE *disk);
int LOAD(FILE *stream, uchar *(*message));
void EXTRACT_BIT(uchar *image, int imageSize);
uchar *ENCODE_MESSAGE(uchar *image, uchar *currentBit, int bitNum);



/****************************************/
/* Clear PGM (XV) comments.             */
/****************************************/
void pgmCommentClear(FILE *disk)
{
	uchar  ch;
	fread(&ch, 1, 1, disk);
	if (ch != '#')
	{
		fseek(disk, -1, SEEK_CUR);
	  return;
	}
	do {
		while (ch != '\n') fread(&ch, 1, 1, disk);
	} while (ch == '#');
	pgmCommentClear(disk);
}


/****************************************/
/* Read PGM formatted image (1D array). */
/****************************************/
uchar *PGM_FILE_READ_1D(char *FileName, int *Width, int *Height, int *color)
{
	int   pmax;
	char  ch;
	char  type[3];
	uchar *Image;
	FILE *disk;
	if ((disk = fopen(FileName, "rb")) == NULL)
	{
		printf("File not found. \n");
		return NULL;
	}

	fscanf(disk, "%s", type);

	if (!strcmp(type, "P6")) //Gets the color of the image? 0 for b/w 1 for full color RGB?
	{
		*color = 1;
	}
	else
	{
		*color = 0;
	}

	fread(&ch, 1, 1, disk);
	pgmCommentClear(disk);


	fscanf(disk, "%d", Width);
	fscanf(disk, "%d", Height);
	fscanf(disk, "%d", &pmax); //can't figure out what pmax is... don't see a use anywhere
	fread(&ch, 1, 1, disk);

	//printf("---Assign Variables Successful\n");

	if (*color == 1) {
		Image = (uchar *)calloc(*Height * *Width * 3, sizeof(uchar));
		fread(Image, 1, (*Height * *Width * 3), disk);
	} else {
		Image = (uchar *)calloc(*Height * *Width, sizeof(uchar));
		fread(Image, 1, (*Height * *Width), disk);
	}

	//printf("Mem Allocation Successful\n");

	fclose(disk);
	return Image;
}


/****************************************/
/* Write PGM formatted image (1D array).*/
/****************************************/
void PGM_FILE_WRITE_1D(char *FileName, uchar *Image, int Width, int Height, int color)
{
	FILE *disk;
	disk = fopen(FileName, "wb");
	if (color == 1) fprintf(disk, "P6\n");
              else fprintf(disk, "P5\n");
	fprintf(disk, "%d %d\n", Width, Height);
	fprintf(disk, "255\n");
	if (color == 1) {
		fwrite(Image, 1, (Height * Width * 3), disk);
	}
	else
	{
		fwrite(Image, 1, (Height * Width), disk);
	}
	fclose(disk);
}


void EXTRACT_BIT(uchar *image, int imageSize)
{ //Grab last bit with AND mask ( & ), insert bit with OR mask( | ), shift bit left 1 ( <<1 ).
	//int (*extractedBytes)[imageSize/8];
	uchar currentByte;
	int bitNum = imageSize/8;
	int hitDelim = 0;

	for(int i = 0; i < bitNum && hitDelim < 3 ;i++)
	{
		for(int x = 0; x < 8;x++)
		{
			currentByte = currentByte << 1;
			currentByte = (currentByte) | (*image & 1);

			//printf("%u <- %u\n", currentByte, *image & 1);
			image++;
		}
		printf("%c", currentByte);
		if (currentByte == 'x'){hitDelim++;}
		else{hitDelim=0;}
	}
	printf("\n");
	return;
}


uchar *ENCODE_MESSAGE(uchar *image, uchar *currentBit, int bitNum)
{
	uchar *temp = image;

	for(int i = 0; i < bitNum;i++)
	{
		//*currentBit = (~*currentBit);
		for(int x = 0; x < 8; x++)
		{
			*temp = (*temp & 254) | (*currentBit>>7);
			*currentBit = *currentBit<<1;
			temp++;
		}
		currentBit++;
	}
	return image;
}

int LOAD(FILE *stream, uchar *(*message))
{
	int amount = 0;
	fseek(stream, 0, SEEK_END);
	amount = ftell(stream);
	rewind(stream);

	*message = malloc(amount);

	fread(*message,1,amount, stream);
	return amount;
}


int main(int argv, char**argc)
{

	if(argv < 2)
	{
		printf("*********************************************\n");
		printf("* HW10 usage:                               *\n");
		printf("* ./hw10 normal <-- Normal operation        *\n");
		printf("* ./hw10 extra  <-- Extra credit operation  *\n");
		printf("*********************************************\n");
		exit(0);
	}

	int *Height=malloc(sizeof(int));
	int *Width=malloc(sizeof(int));
	int *color=malloc(sizeof(int));
	uchar *image = NULL;

	if(!strcmp(argc[1], "normal"))
	{
		image = PGM_FILE_READ_1D("hw10.pgm", Width, Height, color);

		//printf("---Image: %u Height: %d Width: %d color: %d\n",*image, *Height, *Width, *color);

		EXTRACT_BIT(image, (*Height) * (*Width));
	}
	else if(!strcmp(argc[1], "extra"))
	{
		image = PGM_FILE_READ_1D("hw10-Extra.pgm", Width, Height, color);

		if(image==NULL)
		{
			image = PGM_FILE_READ_1D("TajMahal.pgm", Width, Height, color);
		}
		if(image==NULL)
		{
			image = PGM_FILE_READ_1D("hw10.pgm", Width, Height, color); //Fallback if all other options fail...
		}																//This one has to exist.
		if(image==NULL){printf("No valid file to write could be found.\n"); exit(0);}

		//printf("---Image: %u Height: %d Width: %d color: %d\n",*image, *Height, *Width, *color);

		FILE *stream = fopen("hw10-Extra.text", "rb");
		if(stream==NULL){printf("File, \"hw10-Extra.text\", not found\n");exit(0);		}
		uchar *message = NULL;
		int sizeOfMessage = LOAD(stream, &message);
		fclose(stream);

		image = ENCODE_MESSAGE(image, message, sizeOfMessage);
		//EXTRACT_BIT(image, (*Width)*(*Height)); //Testing

		PGM_FILE_WRITE_1D("hw10-Extra.pgm", image, *Width, *Height, *color);

		/*
		//FOR TESTING
		image = PGM_FILE_READ_1D("hw10-Extra.pgm", Width, Height, color);
		//printf("---Image: %u Height: %d Width: %d color: %d\n",*image, *Height, *Width, *color);
		EXTRACT_BIT(image, (*Height) * (*Width));
		//FOR TESTING
		*/

		free(message);
		message = NULL;
	}
	else if(!strcmp(argc[1], "testing"))
	{
		image = PGM_FILE_READ_1D("hw10-Extra.pgm", Width, Height, color);
		//printf("---Image: %u Height: %d Width: %d color: %d\n",*image, *Height, *Width, *color);
		EXTRACT_BIT(image, (*Height) * (*Width));
	}
	else
	{
		printf("invalid command\n");
	}

	free(image); free(Height); free(Width); free(color);
	image = NULL; Height = NULL; Width = NULL; color = NULL;

	return 0;
}
