/***************************************************************************
 *   Copyright (C) 2006, 2007, 2008 by Michael Fischer                     *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

// Interface for generic symbol table data structure.
// This consists of a table of user-owned objects.
// Each object is assumed to have an embedded key string.
// User supplies function for finding the key.
// User also supplies functions for freeing and printing the object.

#ifndef SYMTAB_H
#define SYMTAB_H

// -----------------------------------------------------------------------
// global constant
// -----------------------------------------------------------------------
// The pointer "NOT_FOUND" is returned by lookupSymbtab() to indicate that
// the search failed to find an object matching the search key.
// We don't use the NULL pointer for this purpose because NULL could be a
// valid user pointer.
// We instead use a special pointer that can't be a valid user pointer.
extern void* const NOT_FOUND; // special pointer meaning "key not found"

// -----------------------------------------------------------------------
// Opaque type
typedef struct symtab* Symtab;
typedef const struct symtab* const_Symtab;

// -----------------------------------------------------------------------
// Types for element-specific user-supplied functions
typedef void (*FreeElementFun)(const void* data);
typedef const char* (*KeyFun)(const void* data);
typedef void (*PrintElementFun)(const void* data);

// -----------------------------------------------------------------------
// Element descriptor type
typedef struct {
	FreeElementFun freeElement;
	KeyFun keyString;
	PrintElementFun printElement;
} ElementDesc;

// -----------------------------------------------------------------------
// Public function prototypes
Symtab      newSymtab(const ElementDesc* ed);
void        freeSymtab(Symtab table);
void        insertSymtab(Symtab table, const void* data);
const void* lookupSymtab(const_Symtab table, const char* key);
void        printSymtab(const_Symtab table);
#endif
