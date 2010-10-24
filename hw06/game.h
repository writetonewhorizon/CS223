/*
	Created by: Douglas von Kohorn
	Course: CS223
	Term: Spring 2008
	Problem Set #7
*/

#ifndef GAME_H_
#define GAME_H_

#include <stdbool.h>
#include "hexboard.h"

typedef
struct game* Game;

typedef
enum {GameInProgress, GameWonRed, GameWonBlue} GameState;

Game newGame( Hexboard hb );
void freeGame( Game gm );
Hexboard getHexboardGame( Game gm );
bool playGame( Game gm, double x, double y );
bool undoGame( Game gm );
bool redoGame( Game gm );

#endif /*GAME_H_*/
