/*created by: Douglas von Kohorn
PS9
*/
// Michael J. Fischer
// CPSC 223b, Spring 2008
// Problem set 9: Huffman code

/*
 *  codetable.h
 *
 *  Created by Michael Fischer on 2/16/06.
 *  fischer-michael@cs.yale.edu
 *  For use in Yale course CPSC 223b, Spring 2006
 *
 *  Copyright (C) 2006 by Michael Fischer. All rights reserved.
 *
 */

#ifndef CODETABLE_H_
#define CODETABLE_H_

/* --------------------------------------------------------------------- */

typedef struct codetable* Codetable;
typedef const struct codetable* const_Codetable;

Codetable newCodetable( void );
Codetable newCodetableFromFile( const char* fname );
void      freeCodetable( Codetable ct );

void      insertCodetable( Codetable ct, byte clear, const_Bitstring ctree );
Bitstring getCodeword( const_Codetable, int clear );
void      printCodetable( const_Codetable ct );
void      fwriteCodetable( const char* fname, Codetable ct );

#endif
