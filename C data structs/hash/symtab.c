/***************************************************************************
 *   Copyright (C) 2006, 2007 by Michael Fischer                           *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2007                         *
 ***************************************************************************/

/* hash table implementation of symbol table interface */

#include <stdlib.h>
#include <string.h>
#include "symtab-private.h"

/* -----------------------------------------------------------------------
 * implementation of symtab constants and functions
 * ----------------------------------------------------------------------- */

// Create unique pointer to mean "search key not found"
int dummy;
void* const NOT_FOUND = &dummy;

// -----------------------------------------------------
// Create symbol table
symtab new_symtab( void )
{
  symtab table = malloc( sizeof *table );
  for (int k=0; k<NBuckets; k++) {
    table->bucket[ k ] = NULL;
  }
  return table;
}

// -----------------------------------------------------
// Free symbol table
void free_symtab( symtab table )
{
  for (int k=0; k<NBuckets; k++) {
    free_chain( table->bucket[ k ] );
  }
  free( table );
}

// -----------------------------------------------------
// Insert key-value pair in symbol
// Ownership of the value object transfers to the symbab
void insert( symtab table, const char* key, void* value )
{
  int bn = hash( key, NBuckets );
  cell c = find_cell( table->bucket[ bn ], key );
  if ( c == NULL ) {		/* key not present */
    cell c = new_cell( key, value );
    c->next = table->bucket[ bn ];
    table->bucket[ bn ] = c;
  }
  else {			/* key found */
    free( c->value );
    c->value = value;
  }
}

// -----------------------------------------------------
// Lookup key in symbol table
// If found, return pointer to corresponding value
// If not found, return special pointer NOT_FOUND
void* lookup( const_symtab table, const char* key )
{
  int bn = hash( key, NBuckets );
  cell c = find_cell( table->bucket[ bn ], key );
  return (c == NULL) ? NOT_FOUND : c->value;
}

// =====================================================
// Local functions
// -----------------------------------------------------
// Create a new cell
cell new_cell( const char* key, void* value )
{
  cell c = malloc( sizeof *c );
  c->key = malloc( strlen(key) + 1 );
  strcpy( c->key, key );
  c->value = value;
  c->next = NULL;
  return c;
}

// -----------------------------------------------------
// Free a single cell
void free_cell( cell c )
{
  free( c->key );
  free( c->value );
  free( c );
}

// -----------------------------------------------------
// Free a linked chain of cells
void free_chain( cell c )
{
  cell next;
  while (c != NULL) {
    next = c->next;
    free_cell( c );
    c = next;
  }
}

// -----------------------------------------------------
// Find a cell in a chain
cell find_cell( cell c, const char* key )
{
  while (c != NULL) {
    if( strcmp( c->key, key ) == 0 ) return c;
    c = c->next;
  }
  return NULL;
}

// -----------------------------------------------------
// Compute hash value in range [0..nBuckets-1] from string s
int hash( const char* s, int nBuckets )
{
  unsigned long hashcode = 0;
  for ( int i=0; s[i] != '\0'; i++ ) {
    hashcode = hashcode * Multiplier + s[i];
  }
  return (hashcode % nBuckets);
}

