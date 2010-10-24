/***************************************************************************
 *   Copyright (C) 2006, 2007 by Michael Fischer                           *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2007                         *
 ***************************************************************************/

/*
 *  symtab.h
 */

#ifndef SYMTAB_H
#define SYMTAB_H

/* constant */
extern void* const NOT_FOUND;	// special pointer meaning "key not found"

/* opaque type */
typedef struct symtab* symtab;
typedef const struct symtab* const_symtab;

/* prototypes */
/* allocate and initialize new symbol table */
symtab new_symtab( void );

/* free symbol table and values contained therein */
void free_symtab( symtab table );

/* insert (key, value) pair in table
 * key string is copied
 * value is heap-allocated object; ownership transfers to symbol table
 */
void insert( symtab table, const char* key, void* value );

/* find pair with matching key and return corresponding value
 * returns NOT_FOUND if no matching key
 */
void* lookup( const_symtab table, const char* key );

#endif
