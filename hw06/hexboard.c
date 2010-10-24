/*
	Created by: Douglas von Kohorn
	Course: CS223
	Term: Spring 2008
	Problem Set #6
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "util.h"
#include "hexboard.h"

// private type
typedef 
struct {
	int row;
	int col;
	CellContents val;
} HexCell;

// implementation of opaque type
struct hexboard {
	int size;
	HexCell** cell;
	Geometry geo;
};

// -------------------------------------------------------------------
// Creates a hex board with size rows and columns.
// Center of hex cell (0,0) is at screen coordinate (x0, y0)
// Side of a hexagon has length s
Hexboard newHex( int size, double x0, double y0, double s )
{
	// allocate the hex board
	Hexboard hb = safe_malloc( sizeof( *hb ));
	hb->size = size;
	
	// allocate the backbone array
	hb->cell = safe_malloc( size*sizeof( *hb->cell ));
	
	// allocate each row
	for (int r=0; r<size; r++) {
		hb->cell[r] = safe_malloc( size*sizeof( **hb->cell ));
	}
	
	// initialize each row with its row and col position
	for (int r=0; r<size; r++) {
		for (int c=0; c<size; c++) {
			HexCell* hc = &hb->cell[r][c];
			hc->row = r;
			hc->col = c;
			hc->val = Empty;
		}	
	}
	
	// initialize screen coordinates
	double h = s*sqrt(3.0)/2.0;	// distance from center of hexagon to side
	Geometry* g = &hb->geo;
	g->x0 = x0;
	g->y0 = y0;
	g->x1 = x0 + h*(3.0*size - 1.0);
	g->y1 = y0 + s*(1.5*size + 0.5);
	g->h = h;
	g->s = s;
	return hb;
}

// -------------------------------------------------------------------
// frees hex board
void freeHex( Hexboard hb )
{
	// free each row
	for (int k=0; k < hb->size; k++) 
		free( hb->cell[k] );
	// free the backbone
	free( hb->cell );
	// free the hex board
	free( hb );
}

// -------------------------------------------------------------------
// stores new contents in hex cell
Status putCellHex( Hexboard hb, int row, int col, CellContents val )
{
	if ( row < 0 || row >= hb->size || col < 0 || col >= hb->size ) 
		return OffBoard;
	hb->cell[row][col].val = val;
	return OK;
}
	
// -------------------------------------------------------------------
// returns contents of a hex cell
Status getCellHex( Hexboard hb, int row, int col, CellContents* valp )
{
	if ( row < 0 || row >= hb->size || col < 0 || col >= hb->size ) {
		return OffBoard;
	}
	
	*valp = hb->cell[row][col].val;
	return OK;
}

// -------------------------------------------------------------------
// Returns board size.
int boardSizeHex( Hexboard hb )
{
	return hb->size;
}

// Returns board geometry.
const Geometry* getGeoHex( Hexboard hb )
{
	return &hb->geo;	
}

// -------------------------------------------------------------------
// get row and column numbers of hexagon containing point (x,y)
// returns LocOffBoard if (x,y) is not in any hexagon on the board
Status findHex( Hexboard hb, double x, double y, 
		int* rowp, int* colp )
{
	// find row and col of cell given screen coordinates
	// of any point inside it
	
	const Geometry* g = getGeoHex( hb );
	
	// Translate and scale to put center of lower left hexagon
	// at coordinates (0,0) and to have its six neighbors at
	// (2, 0), (1, 1), (-11, 1), (-2, 0), (-1, -1), (-1, 1)
	// xs = (x-x0+h)/h 
	// ys = (y-y0+s)/(1.5*s)
	
	double xs = (x - g->x0 - g->h)/g->h;
	double ys = (y - g->y0 - g->s)/(1.5 * g->s);
	
	// Find integer coordinates of lower left corner of square
	// containing transformed point
	// xcorner = floor(xs)
	// ycorner = floor(ys)
    
	int xcorner = floor(xs);
	int ycorner = floor(ys);
	
	// Find parity of square and corner of square in trapezoid
	// containing (xs, ys)
	// 
	// (xcorner + ycorner) even:  
	//    hexagon centers at lower left and upper right corners
	//    3*(ys-ycorner) + (xs-xcorner) < 2:  lower left
	//    else upper right
    // Othersise:
	//    hexagon centers at upper left and lower right corners
	//    3*(ys-ycorner) - (xs-xcorner) < 1: lower right
	//    else upper left
	// Let xcenter, ycenter be center of located hexagon
	// Note: xcenter and ycenter are both even
	
	int xcenter, ycenter;
	
	if ((xcorner+ycorner)%2 == 0) {
		if (3.0*(ys-ycorner) + (xs-xcorner) < 2.0) {
			xcenter = xcorner;
			ycenter = ycorner;
		}
		else {
			xcenter = xcorner+1;
			ycenter = ycorner+1;
		}
	}
	else {
		if ( 3.0*(ys-ycorner) - (xs-xcorner) < 1.0) {
			xcenter = xcorner+1;
			ycenter = ycorner;
		}
		else {
			xcenter = xcorner;
			ycenter = ycorner+1;
		}
	}
	
	// Find [row, col] of center
	// row = dimen - ycenter - 1
	// col = (xcenter - ycenter)/2
	
	*rowp = hb->size - ycenter - 1;
	*colp = (xcenter - ycenter)/2;
	
	if (*rowp<0 || *rowp>=hb->size || *colp<0 || *colp>=hb->size)
		return OffBoard;
	else
		return OK;
}

// -------------------------------------------------------------------
// Displays the hex board using character graphics
void displayBoardHex(Hexboard hb) {
	int size = boardSizeHex(hb);
	int row, col;
	CellContents val;

	for (row=0; row<size; row++) {
		// indent current row
		int spaces = size-row+1;
		for (int k=0; k<spaces; k++)
			printf(" ");

		// print row		
		for (col=0; col<size; col++) {
			switch (getCellHex(hb, row, col, &val)) {
			case OK:
				switch (val) {
				case Empty:
					printf(" .");
					break;
				case Red:
					printf(" r");
					break;
				case Blue:
					printf(" b");
					break;
				}
				break;
			case OffBoard:
				fatal("Out of bounds reference to cell [%d,%d]", row, col);
			}
		}
		// end current row
		printf("\n");
	}
}


