// Michael J. Fischer
// CPSC 223b, Spring 2008
// Problem set 9: Huffman code

/*
 *  ibitstream.h
 *
 *  Created by Michael Fischer on 2/16/06.
 *  fischer-michael@cs.yale.edu
 *  For use in Yale course CPSC 223b, Spring 2006
 *
 *  Copyright (C) 2006 by Michael Fischer. All rights reserved.
 *
 */

// Module to read a packed bit string a bit at a time
// from an open byte stream.
// A bit string is packed into a file by first padding it
// with 0's to make its length a multiple of 8.
// Each group of 8 bits are packed into a byte.
// An extra byte is appended to the byte stream giving
// the number of bits of padding in the last data byte.
// 
// getIbitstream() reads and returns the next bit of the stream.
// It returns EOF (-1) when no more bits remain.

// Note: Closing an Ibitstream does not close the underlying
// input byte stream.

#ifndef IBITSTREAM_H_
#define IBITSTREAM_H_

#include <stdbool.h>
#include <stdio.h>

// Public opqaue types
typedef struct ibitstream* Ibitstream;
typedef const struct ibitstream* const_Ibitstream;

// Prototypes
Ibitstream openIbitstream( FILE* in );
void closeIbitstream( Ibitstream ibs );
int getIbitstream( Ibitstream ibs );

#endif
