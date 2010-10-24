/***************************************************************************
 *   Copyright (C) 2006, 2007, 2008 by Michael Fischer                     *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

// Hash table implementation of generic symbol table ADT

#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include "cell.h"
#include "util.h"

#define NBuckets 101	// Size of hash table
#define Multiplier (-1664117991L)

// -----------------------------------------------------
// Define incomplete type
struct symtab {
	Cell bucket[ NBuckets ];
	const ElementDesc* ed; // callback functions
};

// -----------------------------------------------------
// Define the special pointer constant "NOT_FOUND"
static char dummy;
void* const NOT_FOUND = &dummy;

// -----------------------------------------------------
// Private function prototype
static int hashString(const char* s, int nBuckets);

// =====================================================
// Public functions
// -----------------------------------------------------
// Create symbol table
Symtab newSymtab(const ElementDesc* ed) {
	Symtab table = safe_malloc( sizeof *table);
	for (int k=0; k<NBuckets; k++) {
		table->bucket[ k ] = NULL;
	}
	table->ed = ed;
	return table;
}

// -----------------------------------------------------
// Free symbol table
void freeSymtab(Symtab table) {
	for (int k=0; k<NBuckets; k++) {
		freeChain(table->bucket[ k ], table->ed->freeElement);
	}
	free(table);
}

// -----------------------------------------------------
// Insert key-value pair in symbol
// Ownership of the value object transfers to the Symtab
void insertSymtab(Symtab table, const void* data) {
	KeyFun keyFn = table->ed->keyString;
	const char* key = keyFn(data);
	int bn = hashString(key, NBuckets);

	// search for existing key
	Cell c = findCell(table->bucket[ bn ], keyFn, key);
	if (c == NULL) { // key not present
		Cell c = newCell(data);
		c->next = table->bucket[ bn ];
		table->bucket[ bn ] = c;
	} else { // key found, so replace old user data by new
		table->ed->freeElement(c->data);
		c->data = data;
	}
}

// -----------------------------------------------------
// Lookup key in symbol table
// If found, return pointer to corresponding value
// If not found, return special pointer constant NOT_FOUND
const void* lookupSymtab(const_Symtab table, const char* key) {
	KeyFun keyFn = table->ed->keyString;
	int bn = hashString(key, NBuckets);
	Cell c = findCell(table->bucket[ bn ], keyFn, key);
	return (c == NULL) ? NOT_FOUND : c->data;
}

// -----------------------------------------------------
// Print symbol table
void printSymtab(const_Symtab table) {
	for (int bn=0; bn<NBuckets; bn++)
		for (Cell scan = table->bucket[ bn ]; scan!=NULL; scan=scan->next)
			table->ed->printElement(scan->data);
}

// =====================================================
// Private functions
// -----------------------------------------------------
// Compute hash value in range [0..nBuckets-1] from string s
static int hashString(const char* s, int nBuckets) {
	unsigned long hashcode = 0;
	for (int i=0; s[i] != '\0'; i++) {
		hashcode = hashcode * Multiplier + s[i];
	}
	return (hashcode % nBuckets);
}

