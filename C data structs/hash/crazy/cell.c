/***************************************************************************
 *   Copyright (C) 2008 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

// Implementation file for generic linked list cell utility functions

#include <stdio.h>
#include <string.h>
#include "cell.h"
#include "util.h"

// -----------------------------------------------------
// Create a new cell
Cell newCell(const void* data) {
	Cell new = safe_malloc( sizeof *new);
	new->data = data;
	new->next = NULL;
	return new;
}

// -----------------------------------------------------
// Free a single cell
void freeCell(Cell c, FreeElementFun freeElement) {
	freeElement(c->data);
	free(c);
}

// -----------------------------------------------------
// Free a linked chain of cells
void freeChain(Cell c, FreeElementFun freeElement) {
	Cell next;
	while (c != NULL) {
		next = c->next;
		freeCell(c, freeElement);
		c = next;
	}
}

// -----------------------------------------------------
// Find cell in a chain with a matching key string
Cell findCell(Cell c, KeyFun keyFn, const char* key) {
	while (c != NULL) {
		if (strcmp(keyFn(c->data), key) == 0)
			return c;
		c = c->next;
	}
	return NULL;
}

