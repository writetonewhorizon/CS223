/***************************************************************************
 *   Copyright (C) 2008 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

// Interface file for generic linked list cell utilities

#ifndef CELL_H_
#define CELL_H_

#include "symtab.h"

// -----------------------------------------------------
// Public type
typedef struct cell {
	const void* data; // user data object
	struct cell* next;
}* Cell;

// -----------------------------------------------------
// Public functions
Cell newCell(const void* value);
void freeCell(Cell c, FreeElementFun freeElement);
void freeChain(Cell c, FreeElementFun freeElement);
Cell findCell(Cell c, KeyFun keyFn, const char* key);

#endif /*CELL_H_*/
