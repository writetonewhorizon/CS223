/*
	Created by: Douglas von Kohorn
	Course: CS223
	Term: Spring 2008
	Problem Set #7
*/

#include <stdio.h>
#include "util.h"
#include "partition.h"
#include "game.h"
#include <stdbool.h>
#include "hexboard.h"

// -----------------------------------------------------------------
// Define opaque public type
// -----------------------------------------------------------------
struct part {
	int num;					// Size of universe
	struct block* universe;		// Array of blocks
};

// -----------------------------------------------------------------
// Private type
// -----------------------------------------------------------------
// Partition block
struct block {
	int id;						// Block id
	struct block* parent;				// Parent pointer in union-find tree
	bool top, bottom, left, right;
};

// -----------------------------------------------------------------
// Public functions
// -----------------------------------------------------------------

// -----------------------------------------------------------------
// Create a partition of singleton sets over a size num universe
Part newPart( int num )
{
	Part pt = safe_malloc( sizeof *pt );
	pt->num = num;
	pt->universe = safe_malloc( num * sizeof *pt->universe );
	for (int k=0; k<num; k++) {
		Block blk = &pt->universe[k];
		blk->id = k;
		blk->parent = NULL;
		blk->left = false;
		blk->right = false;
		blk->top = false;
		blk->bottom = false;
		if(k % 11 == 0) blk->left = true;
		if(k % 11 == 10) blk->right = true;
		if(k < 11) blk->top = true;
		if(k >= 110) blk->bottom = true;
	}
	return pt;
}

// -----------------------------------------------------------------
// Destroy partition
void  freePart( Part pt )
{
	free( pt->universe );
	free( pt );
}

// -----------------------------------------------------------------
// Return size of the universe of elements
int sizePart( const_Part pt )
{
	return pt->num;
}

// -----------------------------------------------------------------
// Find the block containing element k
int findPart( const_Part pt, int k )
{
	// Simple, non-path-collapsing find
	Block blk = &pt->universe[k];
	while ( blk->parent != NULL ) blk = blk->parent;
	return blk->id;
}

// -----------------------------------------------------------------
// Replace blocks k1 and k2 in partition pt by their union
int unionPart( Part pt, int k1, int k2 ) {
	// Check arguments and get blocks
	if (k1<0 || k1 >= pt->num || k2<0 || k2 >= pt->num)
		fatal( "Argument to unionBlock() out of range" );
	Block blk1 = &pt->universe[k1];
	Block blk2 = &pt->universe[k2];
	if (blk1->parent || blk2->parent)
		fatal( "Argument to unionBlock() is not a block ID" );
	if (blk1==blk2) return blk1->id;	// nothing to do
	
	// Make root1 the root of the union block
	blk2->parent = blk1;
	blk1->top = (blk1->top || blk2->top);
	blk1->bottom = (blk1->bottom || blk2->bottom);
	blk1->left = (blk1->left || blk2->left);
	blk1->right = (blk1->right || blk2->right);
	
	// Return ID of union block
	return blk1->id;
}

// -----------------------------------------------------------------
void printPart( const_Part pt )
{
	int root;
	for (int k=0; k<pt->num; k++) {
		root = findPart( pt, k );
		printf( "Element %i belongs to block %i\n",
				pt->universe[k].id, root );
	}
}

void resolveGameState(const_Part pt, int id, GameState* state, Hexboard brd)
{
	Block temp = &pt->universe[id];
	int row = id / 11;
	int col = id % 11;
	CellContents contents;
	getCellHex(brd,row,col,&contents);
	if(temp->left && temp->right && contents == Red) *state = GameWonRed;
	if(temp->top && temp->bottom && contents == Blue) *state = GameWonBlue;
}

void nullRoot(Part pt,int yroot)
{
	Block temp = &pt->universe[yroot];
	temp->parent = NULL;
}
