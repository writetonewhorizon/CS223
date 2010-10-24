/*
	Created by: Douglas von Kohorn
	Course: CS223
	Term: Spring 2008
	Problem Set #5
*/
#include <stdio.h>
#include "util.h"
#include "hexboard.h"

int executeGame(Hexboard hb, FILE* input, int lineNumber, CellContents* redOrBlue);
int getInput(int* xIn, int* yIn, FILE* moveInput, int linenumber);
void changeColors(CellContents* ROB);

int main(int argc, char* argv[])
{
	// check for exactly one command line argument
	if (argc != 2)
	{
		fatal("TOO MANY ARGUMENTS\n", argv[0]);
	}

	char* infile = argv[1];

	// try to open the file
	printf("Starting hex player on input file \"%s\"\n", infile);
	FILE* in; // defines in to be a stream
	in = fopen(infile, "r");
	if (in == NULL)
	{
		fatal("Failed to open file %s for reading\n", infile);
	}

	Hexboard board = newHex(11,0,0,10);
	const Geometry* geom = getGeoHex(board);
	printf("Created board of dimension %i\n",11);
	printf("Bounding box of board: %i %i %lg %lg\n", (int) geom->x0, (int) geom->y0, geom->x1, geom->y1);
	printf("Hexagon dimensions:\n");
	printf("  radius of inscribed circle = %lg\n", geom->h);
	printf("  radius of circumscribed circle = %lg\n", geom->s);
	printf("-----------------------------------------------\n\n");

	int lineno;
	CellContents color = Red;

	for(lineno = 1;;lineno++)
	{
		if(executeGame(board, in, lineno, &color) == EOF) break;
	}

	freeHex(board);

	fclose(in);

	return 0;
}

int executeGame(Hexboard hb, FILE* input, int lineNumber, CellContents* redOrBlue)
{
	int x,y,row,col;
	x = -1;
	y = -1;
	if(getInput(&x,&y,input,lineNumber) == EOF) return EOF;

	Status pointStatus;
 	CellContents contents;

	pointStatus = findHex(hb,x,y,&row,&col);

	if(pointStatus == OffBoard)
	{
		printf("Point (%i,%i) is off the board\n\n", x, y);
		return 0;
	} else
	{
		printf("Point (%i,%i) belongs to cell [%i,%i]\n", x, y, row, col);

		getCellHex(hb,row,col,&contents);

		if(contents != Empty) 
		{
			printf("Cell occupied, point ignored\n\n");
			return 0;
		} else
		{
			putCellHex(hb,row,col,*redOrBlue);

			if(*redOrBlue == Red) printf("Playing red (r) in cell [%i,%i]\n",row,col);
			else printf("Playing blue (b) in cell [%i,%i]\n",row,col);

			displayBoardHex(hb);
			changeColors(redOrBlue);
		}
	}

	return 0;
}

int getInput(int* xIn, int* yIn, FILE* moveInput, int linenumber)
{
	int ret, ch;

	ret = fscanf(moveInput, "%d%d", xIn, yIn);
	if(ret != 2)
	{
		if(feof(moveInput) && (*xIn == -1 && *yIn == -1)) return EOF;
		if(ferror(moveInput)) fatal("Error reading file\n");
		if(*xIn == -1 || *yIn == -1) fatal("Not even number of entries; problem with input file.");
	}

	ch = fgetc(moveInput);

	if(*xIn < 0) fatal("Incorrect file input, linenumber: %i\n", linenumber);

	if(*yIn < 0) fatal("Incorrect file input, linenumber: %i\n", linenumber);

	return 0;
}

void changeColors(CellContents* ROB)
{
	if(*ROB == Red) *ROB = Blue;
	else *ROB = Red;
}
