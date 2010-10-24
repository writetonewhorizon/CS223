// Michael J. Fischer
// CPSC 223b, Spring 2008
// Problem set 9: Huffman code

/*
 *  bitstring.h
 *
 *  Created by Michael Fischer on 2/16/06.
 *  fischer-michael@cs.yale.edu
 *  For use in Yale course CPSC 223b, Spring 2006
 *
 *  Copyright (C) 2006 by Michael Fischer. All rights reserved.
 *
 */

/*
Description: A Bitstring is an arbitrary length string of bits.  This
abstraction allows bitstrings to be constructed from the packed bits
in a sequence of bytes, by copying another Bitstring, or by appending
the bits one by one.  Bits can also be removed from the right end.
A BitstringIter iterates over the bits in a Bitstring.
*/

#ifndef BITSTRING_H_
#define BITSTRING_H_

#include <stdbool.h>
#include <stdio.h>

typedef unsigned char byte;
typedef struct bitstring* Bitstring;
typedef const struct bitstring* const_Bitstring;
typedef struct bs_iter* BitstringIter;

/* prototypes */
Bitstring newBitstring( void );
Bitstring newBitstringFromBytes( int, const byte* );
Bitstring newBitstringCopy( const_Bitstring );
void freeBitstring( Bitstring );

bool isEmptyBitstring( const_Bitstring );
int getLengthBitstring( const_Bitstring );
int popBackBitstring( Bitstring );
void pushBackBitstring( Bitstring, int );

void fprintBitstring( FILE*, const_Bitstring );
void streamWriteBitstring( FILE*, const_Bitstring );
Bitstring streamReadBitstring( FILE* );

/* iterates over bits */
BitstringIter newBitstringIter( const_Bitstring );
void freeBitstringIter( BitstringIter );
bool hasNextBitstringIter( BitstringIter );
int nextBitstringIter( BitstringIter );

#endif
