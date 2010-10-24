// Michael J. Fischer
// CPSC 223b, Spring 2008

#ifndef GAME_H_
#define GAME_H_

#include <stdbool.h>
#include "hexboard.h"

typedef
enum { GameInProgress, GameWonRed, GameWonBlue }
GameState;

typedef
struct game* Game;

Game newGame( Hexboard hb );
void freeGame( Game gm );
Hexboard getHexboardGame( Game gm );
GameState getStateGame( Game gm );
bool playGame( Game gm, double x, double y );
bool undoGame( Game gm );
bool redoGame( Game gm );

#endif /*GAME_H_*/
