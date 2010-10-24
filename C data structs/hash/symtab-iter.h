/***************************************************************************
 *   Copyright (C) 2006, 2007 by Michael Fischer                           *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2007                         *
 ***************************************************************************/

#ifndef SYMTAB_ITER_H
#define SYMTAB_ITER_H

#include <stdbool.h>
#include "symtab.h"

/* public interface - iterator extension to symtab ADT */

/* type definitions */
typedef struct symtab_iter* symtab_iter;

/* prototypes */

/* create and initialize iterator */
symtab_iter new_symtab_iter( symtab table );

/* free iterator */
void free_symtab_iter( symtab_iter it );

/* test if iterator has next element */
bool has_next_symtab_iter( symtab_iter it );

/* advance iterator to next element and return it */
char* next_symtab_iter( symtab_iter it );

#endif
