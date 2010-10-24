// Michael J. Fischer
// CPSC 223b, Spring 2008
// Problem set 7: test driver

#include <stdio.h>
#include <stdbool.h>
#include "hexboard.h"
#include "game.h"
#include "util.h"

// prototype
void runGame( Game gm, FILE* in );

// ------------------------------------------------------------------
int main( int argc, const char* argv[] )
{
    // Open test input file
    if (argc!=2) fatal( "Usage: %s testfile", argv[0] );
    FILE* in = fopen( argv[1], "r" );
    if (in==NULL) fatal( "Can't open %s", argv[1] );
    
    // Create hexboard and game
    Hexboard hb = newHex( 11, 100.0, 100.0, 20);
    printf( "Created board of dimension %d\n", boardSizeHex( hb ));
    Game game = newGame( hb );
    
    // Run the game
    runGame( game, in );

    // Clean up
    fclose( in );
    freeGame( game );
    freeHex( hb );
}

// ------------------------------------------------------------------
void runGame( Game gm, FILE* in )
{   
    int n;
    bool boardChanged;
    double x, y;
        
    // Main read loop
    bool quit=false;
    do {
        char cmd;
        
        // Get command letter
        n = fscanf( in, " %c", &cmd );
        if (n != 1) break;  // EOF or error

        boardChanged = false;
        switch (cmd) {
        case 'p':       // play
            n = fscanf( in, "%lg%lg", &x, &y );
            if (n != 2) fatal( "bad coordinates for p command" );
            boardChanged = playGame( gm, x, y);
            break;
        case 'u':       // undo
            boardChanged = undoGame( gm );
            break;
        case 'r':
            boardChanged = redoGame( gm );
            break;
        case 'q':
            quit = true;
            break;
        default:
            fatal( "Bad command letter in file" );
        }
        
        if (boardChanged) {
            displayBoardHex( getHexboardGame(gm) );

            switch (getStateGame(gm)) {
            case GameWonRed:
                printf( "Game over:  Red Wins!!!\n" );
                quit = true;
                break;

            case GameWonBlue:
                printf( "Game over:  Blue Wins!!!\n" );
                quit = true;
                break;

            default:
                break;
            }
        }
    } while (!quit);
    printf( "Goodbye!\n" );
}
