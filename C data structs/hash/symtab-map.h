/***************************************************************************
 *   Copyright (C) 2006, 2007 by Michael Fischer                           *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2007                         *
 ***************************************************************************/

#ifndef SYMTAB_MAP_H
#define SYMTAB_MAP_H

#include "symtab.h"

/* public interface - map extension to symtab ADT */

/* type definition */
typedef void (*symtab_map_fn)( const char* key, const void* value, void* clientData);

/* prototypes */

/* create and initialize map */
void map_symtab( symtab_map_fn fn, symtab table, void* clientData );

#endif
