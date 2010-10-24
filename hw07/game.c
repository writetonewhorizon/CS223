/*
	Created by: Douglas von Kohorn
	Course: CS223
	Term: Spring 2008
	Problem Set #7
*/

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "util.h"
#include "hexboard.h"
#include "game.h"
#include "stack.h"
#include "partition.h"

void changeColors(CellContents* ROB);
GameState getStateGame(Game gm);
CellContents* getNeighbors(int row, int col, Game gm);

// ------------------------------------------------------------------------
// Private structure definition
// ------------------------------------------------------------------------
struct game {
	Hexboard brd;		//game board
	CellContents turn;
	int size; 	//# rows and columns of board
	GameState state; 	// {GameInProgress, GameWonRed, GameWonBlue}
	Stack redoR, redoC, redoColor, undoR, undoC, undoColor, undoXroot, undoYroot, redoXroot, redoYroot;
	Part pt;
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
	gm->undoXroot = newStack();
	gm->undoYroot = newStack();
	gm->redoXroot = newStack();
	gm->redoYroot = newStack();
	gm->state = GameInProgress;
	gm->size = 11;
	gm->pt = newPart(gm->size * gm->size);
	return gm;
}

// ------------------------------------------------------------------------
void freeGame( Game gm )
{
	freePart(gm->pt);
	freeStack(gm->redoR);
	freeStack(gm->redoC);
	freeStack(gm->redoColor);
	freeStack(gm->undoR);
	freeStack(gm->undoC);
	freeStack(gm->undoColor);
	freeStack(gm->undoXroot);
	freeStack(gm->undoYroot);
	freeStack(gm->redoXroot);
	freeStack(gm->redoYroot);
	free( gm );
}

// ------------------------------------------------------------------------
GameState getStateGame( Game gm )
{
    return gm->state;
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
	CellContents* tempNbrs;

	while(!isemptyStack(gm->redoR))
	{
		popStack(gm->redoR);
		popStack(gm->redoC);
		popStack(gm->redoColor);
	}

	while(!isemptyStack(gm->redoXroot))
	{
		popStack(gm->redoXroot);
		popStack(gm->redoYroot);
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

			int x, y, xroot, yroot, newroot;
			x = 11 * row + col;
			xroot = findPart(gm->pt,x);
			tempNbrs = getNeighbors(row,col,gm);
			for(int i = 0; i < 6; i++)
			{
				if(tempNbrs[i] == gm->turn)
				{
					if(i == 0) y = 11 * (row-1) + (col-1);
					if(i == 1) y = 11 * (row-1) + (col);
					if(i == 2) y = 11 * (row) + (col-1);
					if(i == 3) y = 11 * (row) + (col+1);
					if(i == 4) y = 11 * (row+1) + (col);
					if(i == 5) y = 11 * (row+1) + (col+1);
					yroot = findPart(gm->pt,y);
					newroot = unionPart(gm->pt,xroot,yroot);
					pushStack(gm->undoXroot,xroot);
					pushStack(gm->undoYroot,yroot);
					xroot = newroot;
				}
				else
				{
					pushStack(gm->undoXroot,-1);
					pushStack(gm->undoYroot,-1);
				}
			}
			free(tempNbrs);
			resolveGameState(gm->pt,newroot,&gm->state,gm->brd);

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
	int row,col,xroot,yroot;
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

		for(int i = 0; i < 6; i++)
		{
			xroot = topStack(gm->undoXroot);
			yroot = topStack(gm->undoYroot);

			popStack(gm->undoXroot);
			popStack(gm->undoYroot);

			if(xroot >= 0) nullRoot(gm->pt,yroot);

			pushStack(gm->redoXroot,xroot);
			pushStack(gm->redoYroot,yroot);
		}
		return true;
	} else
	{
		return false;
	}
}
// ------------------------------------------------------------------------
bool redoGame(Game gm )
{
	int row,col,xroot,yroot;
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
		for(int i = 0; i < 6; i++)
		{
			xroot = topStack(gm->redoXroot);
			yroot = topStack(gm->redoYroot);

			popStack(gm->redoXroot);
			popStack(gm->redoYroot);

			if(xroot >= 0) unionPart(gm->pt,xroot,yroot);

			pushStack(gm->undoXroot,xroot);
			pushStack(gm->undoYroot,yroot);
		}
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

CellContents* getNeighbors(int r, int c, Game gm)
{
	CellContents* nbrs = safe_malloc(sizeof(*nbrs)*6);
	for(int i = 0; i < 6; i++) nbrs[i] = Empty;
	getCellHex(gm->brd,r-1,c-1,&nbrs[0]);
	getCellHex(gm->brd,r-1,c,&nbrs[1]);
	getCellHex(gm->brd,r,c-1,&nbrs[2]);
	getCellHex(gm->brd,r,c+1,&nbrs[3]);
	getCellHex(gm->brd,r+1,c,&nbrs[4]);
	getCellHex(gm->brd,r+1,c+1,&nbrs[5]);
	return nbrs;
}
