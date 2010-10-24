// Michael J. Fischer
// CPSC 223b, Spring 2008

// Implements union-find algorithm to maintain partition of a set

#include <stdio.h>
#include "util.h"
#include "partition.h"

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
typedef struct block {
	int id;						// Block id
	struct block* parent;		// Parent pointer in union-find tree
	int weight;					// # elements in subtree rooted here
}* Block;

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
		blk->weight = 1;
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
	
	// Swap Blocks if necessary so that blk1->weight >= blk2->weight
	if (blk1->weight < blk2->weight) {
		Block temp = blk1;
		blk1 = blk2;
		blk2 = temp;
	}
	
	// Make root1 the root of the union block
	blk2->parent = blk1;
	blk1->weight += blk2->weight;
	
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
