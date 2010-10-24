// Michael J. Fischer
// CPSC 223b, Spring 2008
// Problem set 9: Huffman code

/*
 *  codetree.h
 *
 *  Created by Michael Fischer on 2/16/06.
 *  fischer-michael@cs.yale.edu
 *  For use in Yale course CPSC 223b, Spring 2006
 *
 *  Copyright (C) 2006 by Michael Fischer. All rights reserved.
 *
 */

#ifndef PFXCODE_H_
#define PFXCODE_H_

#include <stdbool.h>
#include "bitstring.h"
#include "codetable.h"
#include "ibitstream.h"
#include "obitstream.h"

// ==================================================================
// Class definitions
// ------------------------------------------------------------------
// node of code tree
typedef struct node* Node;
typedef const struct node* const_Node;

// code tree
typedef struct codetree* Codetree;
typedef const struct codetree* const_Codetree;

// tree walker
typedef struct walker* Walker;
typedef const struct walker* const_Walker;

// ==================================================================
// Prototypes
// ------------------------------------------------------------------
// prototypes for Node class
Node newNode( void );
void freeNode( Node nd );

// prototypes for Codetree class 
Codetree newCodetree( void );
Codetree newCodetreeFromNode( Node );
Codetree newCodetreeFromFile( const char* fname );
void freeCodetree( Codetree );
void insertCodetree( Codetree ctree, Bitstring bs, byte symbol );
Codetable newCodetableFromCodetree( const Codetree ctree );
void fprintCodetree( FILE* out, const_Codetree ctree );

// prototypes for Walker class
Walker newWalker( const_Codetree );
Walker newWalkerCopy( const_Walker );
void freeWalker( Walker );
void toRootWalker( Walker );			// places walker at root of tree
bool toSonWalker( Walker, int );		// take step down tree
bool atLeafWalker( const_Walker );		// test if we're at a leav
int getValueWalker( Walker );			// get clear text value of current node

#endif
