/*created by: Douglas von Kohorn
PS9
*/
// Michael J. Fischer
// CPSC 223b, Spring 2008
// Problem set 9: Huffman code

/*
 *  obitstream.h
 *
 *  Created by Michael Fischer on 2/16/06.
 *  fischer-michael@cs.yale.edu
 *  For use in Yale course CPSC 223b, Spring 2006
 *
 *  Copyright (C) 2006 by Michael Fischer. All rights reserved.
 *
 */

// Module to write a bit stream to an open byte stream.
// The bits are packed 8 at a time into bytes.
// When the bit stream is closed, any bits that have
// not yet been written out are packed into a 0-filled
// byte and written out, followed by a byte containing
// a count of the number of 0's used to fill the last
// data byte.

// Note: Closing an Obitstream does not close the underlying
// output byte stream.

#ifndef OBITSTREAM_H_
#define OBITSTREAM_H_

#include <stdbool.h>
#include <stdio.h>
#include "bitstring.h"

typedef struct obitstream* Obitstream;
typedef const struct obitstream* const_Obitstream;

/* prototypes */
Obitstream openObitstream( FILE* out );
void closeObitstream( Obitstream obs );
void putbObitstream( Obitstream obs, int bit );
void putsObitstream( Obitstream obs, Bitstring bs );

#endif
