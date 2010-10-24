/***************************************************************************
 *   Copyright (C) 2007 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

// A Flexbuf is an expandable character buffer useful for reading lines
// of non-null characters of arbitrary length from a stream.
//
// Each call to fgetlineFlexbuf() replaces the buffer contents with the
// next line of input and returns the number of characters read.
// Reading stops when a new line character or EOF is reached.
// The new line character is placed in the buffer, if present.
// A return value of 0, meaning no characters were read, can only
// happen because of read error or EOF.
// In all cases, a '\0' is stored after the last character read.
//
// There are two ways of using the contents of the buffer:
// 1) toStringFlexbuf() returns a const char pointer to the buffer
//    that remains valid only until the next call to fgetlineFlexbuf().
//    The Flexbuf object retains ownership of the buffer.
// 2) extractFlexbuf() returns a char pointer to the buffer and
//    transfers ownership to the caller, who is responsible for
//    freeing the storage when no longer needed.  The allocation size
//    of this buffer can be determined by calling buflenFlexbuf().

#ifndef FLEXBUF_H_
#define FLEXBUF_H_

#include <stdio.h>

// Opaque type definitions
typedef struct flexbuf* Flexbuf;
typedef const struct flexbuf* const_Flexbuf;

// Prototypes
Flexbuf     newFlexbuf( void );
void        freeFlexbuf( Flexbuf fb );
int         fgetlineFlexbuf( Flexbuf fb, FILE* in );
const char* toStringFlexbuf( const_Flexbuf fb );
char*       extractFlexbuf( Flexbuf fb );
int         buflenFlexbuf( const_Flexbuf fb );

#endif
