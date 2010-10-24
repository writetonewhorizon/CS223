/*
	Created by: Douglas von Kohorn
	Course: CS223
	Term: Spring 2008
	Problem Set #5
*/

#include <stdio.h>
#include <math.h>
#include "hexboard.h"
#include "util.h"

struct hexboard
{
	int sizeola;
	double leftX;
	double leftY;
	double sidelength;
	CellContents cellBoard[11][11];
};

Geometry geometry;

// Creates a hex board with size rows and columns.
// Computes bounding box and initializes geometry.
// Lower left corner of bounding box of board
// is at coordinates (x0, y0) in plane.
// Side of a hexagon has length s.
Hexboard newHex( int size, double x0, double y0, double s )
{
	Hexboard hb = safe_malloc( sizeof(*hb) );
	hb->sizeola = size;
	hb->leftX = x0;
	hb->leftY = y0;
	hb->sidelength = s;

	geometry.s = s;
	geometry.h = .8660254037*geometry.s;
	geometry.x0 = x0;
	geometry.y0 = y0;
	geometry.x1 = (3.0*size - 1)*geometry.h + x0;
	geometry.y1 = ((3.0*size + 1)*geometry.s)/2.0 + y0;

	int i,j;
	for(i = 0; i < hb->sizeola; i++)
		for(j = 0; j < hb->sizeola; j++)
			hb->cellBoard[i][j] = Empty;

	return hb;
}

// Free hex board
void freeHex( Hexboard hb )
{
	free( hb );
}

// Set cell contents.
// Store val as contents of hexagon number [row, col].
Status putCellHex( Hexboard hb, int row, int col, CellContents val )
{
	if(hb->cellBoard[row][col] != Empty) return OffBoard;
	else hb->cellBoard[row][col] = val;
	return OK;
}

// Copies contents of hexagon number [row, col] into *valp. 
Status getCellHex( Hexboard hb, int row, int col, CellContents* valp )
{
	*valp = hb->cellBoard[row][col];
	if(*valp != Empty) return OffBoard;
	else return OK;
}

// Returns board size.
int boardSizeHex( Hexboard hb )
{
	return hb->sizeola;
}

// Returns board geometry.
const Geometry* getGeoHex( Hexboard hb )
{
	return &geometry;
}

// Finds the hexagon on the board containing point (x,y)
// and returns its number in [*rowp, *colp].  
// Returns status OffBoard if (x,y) does not lie within
// one of the hexagons on the board.
Status findHex( Hexboard hb, double x, double y, int* rowp, int* colp )
{
	double x1,y1,xs,ys;
	int xc,yc,xh,yh;

	if(x < geometry.x0 || x > geometry.x1 || y < geometry.y0 || y  > geometry.y1) 
	{
		printf("%lg | %lg \n",x,y);
		return OffBoard;
	}

	x1 = x - geometry.x0 - geometry.h;
	y1 = y - geometry.y0 - geometry.s;
	xs = x1 / geometry.h;
	ys = y1 / ((3.0*geometry.s)/2.0);
	xc = floor(xs);
	yc = floor(ys);

	if((xc + yc) % 2 == 0)
	{
		if(3*ys - 3*yc + xs - xc - 2 < 0) 
		{
			xh = xc;
			yh = yc;
		} else 
		{
			xh = xc + 1;
			yh = yc + 1;
		}
	} else
	{
		if(3*ys - 3*yc - xs + xc - 1 < 0)
		{
			xh = xc +1;
			yh = yc;
		} else
		{
			xh = xc;
			yh = yc + 1;
		}
	}

	*rowp = hb->sizeola - 1 - yh;
	*colp = (xh-yh)/2;

	if(*rowp < 0 || *rowp > hb->sizeola-1 || *colp < 0 || *colp > hb->sizeola-1) return OffBoard;
	else return OK;
}

// Displays the hex board using character graphics
void displayBoardHex( Hexboard hb )
{
	int i,j,numSpaces;
	for(i = 0; i < hb->sizeola; i++)
	{
		for(numSpaces = i; numSpaces < hb->sizeola; numSpaces++)
		{
			printf(" ");
		}
		for(j = 0; j < hb->sizeola; j++)
		{
			if(hb->cellBoard[i][j] == Empty) printf(". ");
			if(hb->cellBoard[i][j] == Blue) printf("b ");
			if(hb->cellBoard[i][j] == Red) printf("r ");
		}
		printf("\n");
	}
	printf("\n");
}
