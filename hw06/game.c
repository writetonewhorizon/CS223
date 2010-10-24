/*
	Created by: Douglas von Kohorn
	Course: CS223
	Term: Spring 2008
	Problem Set #6
*/

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "util.h"
#include "hexboard.h"
#include "game.h"
#include "stack.h"

void changeColors(CellContents* ROB);

// ------------------------------------------------------------------------
// Private structure definition
// ------------------------------------------------------------------------
struct game {
	Hexboard brd;
	CellContents turn;
	Stack redoR, redoC, redoColor, undoR, undoC, undoColor;
};

// ------------------------------------------------------------------------
// Public functions
// ------------------------------------------------------------------------
Game newGame( Hexboard hb ) {
	Game gm = safe_malloc( sizeof(*gm) );	
	gm->brd = hb;
	gm->turn = Red;		// Red plays first
	gm->redoR = newStack();
	gm->redoC = newStack();
	gm->redoColor = newStack();
	gm->undoR = newStack();
	gm->undoC = newStack();
	gm->undoColor = newStack();
	return gm;
}

// ------------------------------------------------------------------------
void freeGame( Game gm )
{
	free( gm );
}

// ------------------------------------------------------------------------
Hexboard getHexboardGame( Game gm )
{
	return gm->brd;
}

// ------------------------------------------------------------------------
bool playGame(Game gm, double x, double y)
{
	int row,col;
	while(!isemptyStack(gm->redoR))
	{
		popStack(gm->redoR);
		popStack(gm->redoC);
		popStack(gm->redoColor);
	}

	Status pointStatus;
	CellContents contents;

	pointStatus = findHex(gm->brd,x,y,&row,&col);

	if(pointStatus == OffBoard)
	{
		printf("Point (%g,%g) is off the board\n\n", x, y);
		return false;
	} else
	{
		printf("Point (%g,%g) belongs to cell [%i,%i]\n", x, y, row, col);

		getCellHex(gm->brd,row,col,&contents);

		if(contents != Empty) 
		{
			printf("Cell occupied, point ignored\n\n");
			return false;
		} else
		{
			putCellHex(gm->brd,row,col,gm->turn);
			pushStack(gm->undoR,row);
			pushStack(gm->undoC,col);
			pushStack(gm->undoColor,gm->turn);

			if(gm->turn == Red) printf("Playing red (r) in cell [%i,%i]\n",row,col);
			else printf("Playing blue (b) in cell [%i,%i]\n",row,col);

			displayBoardHex(gm->brd);
			changeColors(&(gm->turn));
		}
	}

	printf("playGame called on point (%g, %g)\n", x, y);
	return true;
}

// ------------------------------------------------------------------------
bool undoGame(Game gm )
{
	int row,col;
	CellContents color;

	if(!isemptyStack(gm->undoR))
	{
		row = topStack(gm->undoR);
		col = topStack(gm->undoC);
		color = topStack(gm->undoColor);

		popStack(gm->undoR);
		popStack(gm->undoC);
		popStack(gm->undoColor);

		putCellHex(gm->brd,row,col,Empty);

		pushStack(gm->redoR,row);
		pushStack(gm->redoC,col);
		pushStack(gm->redoColor,color);
		return true;
	} else
	{
		return false;
	}
}
// ------------------------------------------------------------------------
bool redoGame(Game gm )
{
	int row,col;
	CellContents color;

	if(!isemptyStack(gm->redoR))
	{
		row = topStack(gm->redoR);
		col = topStack(gm->redoC);
		color = topStack(gm->redoColor);

		popStack(gm->redoR);
		popStack(gm->redoC);
		popStack(gm->redoColor);

		putCellHex(gm->brd,row,col,color);

		pushStack(gm->undoR,row);
		pushStack(gm->undoC,col);
		pushStack(gm->undoColor,color);
		return true;
	} else
	{
		return false;
	}
}

void changeColors(CellContents* ROB)
{
	if(*ROB == Red) *ROB = Blue;
	else *ROB = Red;
}