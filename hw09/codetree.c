// Michael J. Fischer
// CPSC 223b, Spring 2008
// Problem set 9: Huffman code

/*created by: Douglas von Kohorn
PS9
*/
/*
 *  codetree.c
 *
 *  Created by Michael Fischer on 2/16/06.
 *  fischer-michael@cs.yale.edu
 *  For use in Yale course CPSC 223b, Spring 2006
 *
 *  Copyright (C) 2006 by Michael Fischer. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "util.h"
#include "codetree.h"
#include "bitstring.h"

// Define opaque types

// code tree
struct codetree {
  Node root;
};

// tree walker
struct walker {
  const_Codetree ctree;
  Node curnode;
};

// Private function prototypes
static void walkTree(Codetable ct, Walker scan, Bitstring path);
static void fprintCodetreeHelper(FILE* out, Walker scan, Bitstring path);

// ===================================================================
// Implementation of class functions
// ===================================================================
// Node class
// -------------------------------------------------------------------
// Create a new default node -- no value, no children
Node newNode(void) {
	Node nd = safe_malloc( sizeof *nd);
	nd->value = 0;
	nd->son[0] = nd->son[1] = NULL;
	nd->weight = 0;
	return nd;
}

// -------------------------------------------------------------------
// Free a node and all its descendants
void freeNode(Node nd) {
	if (nd != NULL) {
		freeNode(nd->son[0]);
		freeNode(nd->son[1]);
		free(nd);
	}
}

// ===================================================================
// Codetree class
// ------------------------------------------------------------------
// Create a Codetree with default root node
Codetree newCodetree(void) {
	Codetree ctree = safe_malloc( sizeof *ctree);
	ctree->root = newNode();
	return ctree;
}

// ------------------------------------------------------------------
// Create a Codetree with <nd> as root
Codetree newCodetreeFromNode(Node nd) {
	Codetree ctree = safe_malloc( sizeof *ctree);
	ctree->root = nd;
	return ctree;
}

// -------------------------------------------------------------------
// Import a Codetree from a file
Codetree newCodetreeFromFile(const char* fname) {
	FILE* in = fopen(fname, "r");
	if (in==NULL)
		return NULL;

	Codetree ctree = newCodetree();
	int k; // clear text byte
	for (k=0; k<256; k++) {
		Bitstring bs = streamReadBitstring(in);
		if (bs == NULL)
			break;
		insertCodetree(ctree, bs, k);
		freeBitstring(bs);
	}
	fclose(in);
	if (k<256)
		fatal("Incomplete code file \"%s\"\n", fname);
	return ctree;
}

// -------------------------------------------------------------------
// Free all nodes of tree and tree itself
void freeCodetree(Codetree ctree) {
	freeNode(ctree->root);
	free(ctree);
}

// -------------------------------------------------------------------
// Insert a new leaf with value <symbol> at end of <path>,
// creating nodes along path if necessary.
void insertCodetree(Codetree ctree, Bitstring path, byte symbol) {
	BitstringIter pathi = newBitstringIter(path);
	Node scan = ctree->root;

	while (hasNextBitstringIter(pathi) ) {
		int bit = nextBitstringIter(pathi);

		// create son if necessary
		if (scan->son[ bit ] == NULL)
			scan->son[ bit ] = newNode();

		// walk down a level
		scan = scan->son[ bit ];
	}

	// save value
	scan->value = symbol;

	// clean up
	freeBitstringIter(pathi);
}

// -------------------------------------------------------------------
// Construct codetable from tree.
// Performs a prefix walk of the tree, adding each leaf encountered
// to an initially-empty Codetable.
Codetable newCodetableFromCodetree(Codetree ctree) {
	Codetable ct = newCodetable();
	Walker scan = newWalker(ctree);
	Bitstring path = newBitstring();

	walkTree(ct, scan, path);

	freeBitstring(path);
	free(scan);
	return ct;
}

// -------------------------------------------------------------------
// Recursive walk tree function "helper" function
static void walkTree(Codetable ct, Walker scan, Bitstring path) {
	if (atLeafWalker(scan) ) {
		insertCodetable(ct, getValueWalker(scan), path);
		fprintBitstring(stdout,path);
		printf(" | %i\n",getValueWalker(scan));
	} else {
		for (int b=0; b<2; b++) {
			pushBackBitstring(path, b);
			Walker scanb = newWalkerCopy(scan);
			if ( !toSonWalker(scanb, b) )
				fatal("Invalid code tree -- non-leaf lacks son[b]");
			walkTree(ct, scanb, path);
			popBackBitstring(path);
			freeWalker(scanb);
		}
	}
}

// -------------------------------------------------------------------
// Print Codetree
void fprintCodetree(FILE* out, const_Codetree ctree) {
	Walker scan = newWalker(ctree);
	Bitstring path = newBitstring();

	fprintCodetreeHelper(out, scan, path);

	freeBitstring(path);
	freeWalker(scan);
}

// -------------------------------------------------------------------
// Print tree helper
static void fprintCodetreeHelper(FILE* out, Walker scan, Bitstring path) {
	// Print current node
	if (isEmptyBitstring(path))
		fprintf(out, "Root: ");
	else {
		fprintf(out, "%s ", atLeafWalker(scan) ? "Leaf" : "Node");
		fprintBitstring(out, path);
		fprintf(out, ":");
	}
	// pad with blanks to Bitstring length 30
	for (int k=30-getLengthBitstring(path); k>0; k--)
		putc( ' ', out );
	fprintf(out, ", value = 0x%02x", getValueWalker(scan) );
	fprintf(out, "\n");

	if (atLeafWalker(scan) )
		return;

	// print subtrees
	for (int b=0; b<2; b++) {
		pushBackBitstring(path, b);
		Walker scanb = newWalkerCopy(scan);
		if (!toSonWalker(scanb, b)) {
			fprintf(out, " --son[%d] missing for non-leaf\n", b);
		} else {
			fprintCodetreeHelper(out, scanb, path);
		}
		popBackBitstring(path);
		freeWalker(scanb);
	}
}

// ===================================================================
// Tree walker class
// -------------------------------------------------------------------
Walker newWalker(const_Codetree ctree) {
	Walker scan = safe_malloc( sizeof( *scan ));
	scan->ctree = ctree;
	scan->curnode = ctree->root;
	return scan;
}

// -------------------------------------------------------------------
Walker newWalkerCopy(const_Walker scan) {
	Walker copy = safe_malloc( sizeof( *copy ));
	*copy = *scan;
	return copy;
}

// -------------------------------------------------------------------
void freeWalker(Walker scan) {
	free(scan);
}

// -------------------------------------------------------------------
void toRootWalker(Walker scan) {
	scan->curnode = scan->ctree->root;
}

// -------------------------------------------------------------------
bool toSonWalker( Walker scan, int bit )
{
	if ( scan->curnode->son[ bit ] == NULL ) return false;
	scan->curnode = scan->curnode->son[ bit ];
	return true;
}

// -------------------------------------------------------------------
bool atLeafWalker( const_Walker scan )
{
	return scan->curnode->son[0] == NULL && scan->curnode->son[1] == NULL;
}

// -------------------------------------------------------------------
int getValueWalker(Walker scan) {
	return scan->curnode->value;
}

