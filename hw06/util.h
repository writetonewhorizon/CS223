/*
	Created by: Douglas von Kohorn
	Course: CS223
	Term: Spring 2008
	Problem Set #6
*/

#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

// Prototypes
void* safe_malloc( size_t size );
void* safe_realloc( void *ptr, size_t size );
void fatal( char* format, ... );

#endif
