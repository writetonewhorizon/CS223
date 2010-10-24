/*
	Created by: Douglas von Kohorn
	Course: CS223
	Term: Spring 2008
	Problem Set #6
*/

#include <gtk/gtk.h>
#include <stdio.h>
#include "game.h"
#include "controller.h"
#include "viewer.h"

// ------------------------------------------------------------------------
int main( int   argc,
          char *argv[] )
{
	// Create a hex board
	Hexboard hb = newHex( 11, 100.0, 100.0, 20);

	// Debugging printout
	printf("Created board of dimension %d\n", boardSizeHex( hb ));
	const Geometry* g = getGeoHex( hb );
	printf("Bounding box of board: %g %g %g %g\n", g->x0, g->y0, g->x1, g->y1);
	printf("Hexagon dimensions:\n"
		"  radius of inscribed circle = %g\n"
		"  radius of circumscribed circle = %g\n"
		"-----------------------------------------------\n", g->h, g->s);
	
    // Create the game
    Game game = newGame( hb );
    
    // Run the game
    startController( game, argc, argv );
	
    // Clean up
    freeGame(game);
    freeHex( hb );
}
