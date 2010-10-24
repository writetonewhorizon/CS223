/***************************************************************************
 *   Copyright (C) 2006, 2007 by Michael Fischer                           *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2007                         *
 ***************************************************************************/

#ifndef SYMTAB_PRIVATE_H
#define SYMTAB_PRIVATE_H

#include "symtab.h"

/* private definitions for hash table implementation of symtab ADT */

/* constants */
#define NBuckets 101		/* number of buckets in hash table */
#define Multiplier -1664117991L	/* multiplier for hash function */

/* type definitions */
typedef struct cell {
  char* key;
  void* value;
  struct cell* next;
}* cell;

struct symtab {
  cell bucket[ NBuckets ];
};

/* prototypes for private functions */

/* create and initialize new cell */
cell new_cell( const char* key, void* value );

/* free cell, including key and value fields */
void free_cell( cell c );

/* free chain of cells */
void free_chain( cell c );

/* search chain of cells for given key
 * returns cell if found, NULL if not found
 */
cell find_cell( cell c, const char* key );

/* return hash of string in range [0...nBuckets-1] */
int hash( const char* s, int nBuckets );

#endif
