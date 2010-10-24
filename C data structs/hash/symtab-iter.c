/***************************************************************************
 *   Copyright (C) 2006, 2007 by Michael Fischer                           *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2007                         *
 ***************************************************************************/

/* implementation - iterator extension to symtab ADT */

#include <stdlib.h>
#include <string.h>
#include "symtab-private.h"
#include "symtab-iter.h"

struct symtab_iter {
  symtab table;
  int bn;			/* bucket number */
  cell scan;			/* cell in bucket */
};

/* -----------------------------------------------------------------------
 * private function
 * ----------------------------------------------------------------------- */
/* moves forward to a cell */
void advance_to_cell( symtab_iter it )
{
  while (it->scan == NULL) {
    it->bn++;			            /* advance to next bucket */
    if (it->bn  == NBuckets) break;         /* can't continue */
    it->scan = it->table->bucket[ it->bn ]; /* scan bucket */
  }
}

/* -----------------------------------------------------------------------
 * implementation of symtab iterators
 * ----------------------------------------------------------------------- */

/* create and initialize iterator */
symtab_iter new_symtab_iter( symtab table )
{
  symtab_iter it = malloc( sizeof *it );
  it->table = table;
  it->bn = 0;
  it->scan = table->bucket[ 0 ];
  advance_to_cell( it );
  return it;
}

/* free iterator */
void free_symtab_iter( symtab_iter it )
{
  free( it );
}

/* test if iterator has next element */
bool has_next_symtab_iter( symtab_iter it )
{
  return (it->bn < NBuckets);
}

/* advance iterator to next element and return it */
char* next_symtab_iter( symtab_iter it )
{
  char* key = it->scan->key;
  it->scan = it->scan->next;
  advance_to_cell( it );
  return key;
}


