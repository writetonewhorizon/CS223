/***************************************************************************
 *   Copyright (C) 2006, 2007, 2008 by Michael Fischer                     *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

// Interface file for a Record object with associated key and value strings

#ifndef RECORD_H
#define RECORD_H

// -----------------------------------------------------------------------
// Opaque types
// -----------------------------------------------------------------------
typedef struct record* Record;
typedef const struct record* const_Record;

// -----------------------------------------------------------------------
// Function prototypes
// -----------------------------------------------------------------------
Record newRec( const char* name, const char* val );
void   freeRec( const_Record rec );
const  char* keyRec( const_Record rec );
void   printRec( const_Record rec );

#endif
