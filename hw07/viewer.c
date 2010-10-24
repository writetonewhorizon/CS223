// Michael J. Fischer
// CPSC 223b, Spring 2008

#include <cairo.h>
#include "viewer.h"

// ------------------------------------------------------------------------
// Draw a hexagon at base point with screen coordinates (xsc,ysc)
// of size (2h, 2s).
// Base point is lower left corner of bounding box of hexagon.
static void drawHex(cairo_t* cr, double xsc, double ysc, double h, double s)
{
	cairo_move_to(cr, xsc, ysc);	// base point of hexagon (lower left corner)
	cairo_rel_move_to(cr, h, 2*s); // top point of hexagon
	cairo_rel_line_to(cr, h, -s/2.0);
	cairo_rel_line_to(cr, 0, -s);
	cairo_rel_line_to(cr, -h, -s/2.0);
	cairo_rel_line_to(cr, -h, s/2.0);
	cairo_rel_line_to(cr, 0,  s);
	cairo_close_path(cr);
}

// ------------------------------------------------------------------------
// Draw a Hex game board on a cairo canvas cr
void displayGame(Game gm, cairo_t* cr)
{
	Hexboard hb = getHexboardGame( gm );
	const Geometry* geo = getGeoHex( hb );
	int size = boardSizeHex( hb );
	
	// int width, height;
	cairo_set_line_width(cr, 1);
	
	double xsc, ysc;	// cairo screen coordinates!
	double s = geo->s;
	double h = geo->h;

	int row;
	int col;
	CellContents val;

	for (row=0; row<size; row++)
		for (col=0; col<size; col++) {
			getCellHex( hb, row, col, &val );
			
			xsc = 2*col*h + h*(size-row-1);
			ysc = 3*s/2*row;
			
			drawHex(cr, xsc, ysc, h, s);

			switch(val) {
			case Empty:
				cairo_set_source_rgb(cr, 1, 1, 1);
				break;
			case Red:
				cairo_set_source_rgb(cr, 0.69, 0.19, 0);
				break;
			case Blue:
				cairo_set_source_rgb(cr, 0.3, 0.4, 0.6);
				break;
			}
			cairo_fill_preserve(cr);

			cairo_set_source_rgb(cr, 0, 0, 0);
			cairo_stroke(cr);
		}

}
