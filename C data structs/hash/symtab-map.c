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
#include "symtab-map.h"

/* -----------------------------------------------------------------------
 * implementation of symtab map function
 * ----------------------------------------------------------------------- */

void map_symtab( symtab_map_fn fn, symtab table, void* clientData )
{
  int bn;
  cell scan;

  for (bn=0; bn<NBuckets; bn++)
    for (scan = table->bucket[ bn ]; scan!=NULL; scan=scan->next)
      fn( scan->key, scan->value, clientData );
}
