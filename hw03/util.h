/***************************************************************************
 *   Copyright (C) 2007 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2007                         *
 ***************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

// Prototypes
void* safe_malloc( size_t size );
void* safe_realloc( void *ptr, size_t size );
void fatal( char* format, ... );

#endif
