/*
	Created by: Douglas von Kohorn
	Course: CS223
	Term: Spring 2008
	Problem Set #7
*/

#ifndef PARTITION_H_
#define PARTITION_H_

#include <stdio.h>
#include "util.h"
#include "partition.h"
#include "game.h"
#include <stdbool.h>
#include "hexboard.h"

// --------------------------------------------------------
// Partition on the integers {0, ..., n-1}
typedef struct part* Part;
typedef const struct part* const_Part;
typedef struct block* Block;

// --------------------------------------------------------
// Partition functions
// --------------------------------------------------------

// Create a partition of size num of singleton blocks
Part newPart( int num );

// Destroy partition
void freePart( Part pt );

// Return size of the universe of elements
int sizePart( const_Part pt );

// Find ID of block containing element k
int findPart( const_Part pt, int k );

// Replace blocks k1 and k2 in partition pt by their union
int unionPart( Part pt, int k1, int k2 );

// Print the partition
void printPart( const_Part pt );

void resolveGameState(const_Part pt, int id, GameState* state, Hexboard brd);

void nullRoot(Part part,int yroot);

#endif /*PARTITION_H_*/
