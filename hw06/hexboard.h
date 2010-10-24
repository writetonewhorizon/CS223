/*
	Created by: Douglas von Kohorn
	Course: CS223
	Term: Spring 2008
	Problem Set #6
*/

#ifndef HEXBOARD_H_
#define HEXBOARD_H_

// =====================================================================
// Type definitions
// =====================================================================

// Status return values
typedef
enum { OK, OffBoard } Status;

// Cell contents values
typedef
enum { Empty, Red, Blue } CellContents;

typedef
struct hexboard* Hexboard;

typedef
struct {
    double x0;  // Cartesian coordinate of left edge of bounding box
    double y0;  // Cartesian coordinate of bottom edge of bounding box
    double x1;  // Cartesian coordinate of right edge of bounding box
    double y1;  // Cartesian coordinate of top of bounding box
    double h;   // distance from center of hexagon to a side
    double s;   // length of side of a hexagon
} Geometry;

// =====================================================================
// Prototypes
// =====================================================================

// Creates a hex board with size rows and columns.
// Computes bounding box and initializes geometry.
// Lower left corner of bounding box of board
// is at coordinates (x0, y0) in plane.
// Side of a hexagon has length s.
Hexboard newHex( int size, double x0, double y0, double s );

// Free hex board
void freeHex( Hexboard hb );

// Set cell contents.
// Store val as contents of hexagon number [row, col].
Status putCellHex( Hexboard hb, int row, int col, CellContents val );
    
// Copies contents of hexagon number [row, col] into *valp. 
Status getCellHex( Hexboard hb, int row, int col, CellContents* valp );

// Returns board size.
int boardSizeHex( Hexboard hb );

// Returns board geometry.
const Geometry* getGeoHex( Hexboard hb );

// Finds the hexagon on the board containing point (x,y)
// and returns its number in [*rowp, *colp].  
// Returns status OffBoard if (x,y) does not lie within
// one of the hexagons on the board.
Status findHex( Hexboard hb, double x, double y, int* rowp, int* colp );

// Displays the hex board using character graphics
void displayBoardHex( Hexboard hb );

#endif /*HEXBOARD_H_*/
