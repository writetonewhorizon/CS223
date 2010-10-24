/***************************************************************************
 *   Copyright (C) 2008 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#include <stdlib.h>
#include "stack.h"
#include "util.h"

// -------------------------------------------------------------------------
// array-based stack
// -------------------------------------------------------------------------

#define INITIAL_SIZE 10

// Definition of opaque type
struct stack {
	T* elements;
	int cursize;
	int maxsize;
};

// -------------------------------------------------------------------------
Stack newStack( void )
{
	Stack s = safe_malloc( sizeof *s );
	s->elements = safe_malloc( INITIAL_SIZE * sizeof *s->elements );
	s->cursize = 0;
	s->maxsize = INITIAL_SIZE;
	return s;
}

// -------------------------------------------------------------------------
void freeStack( Stack s )
{
	free( s->elements );
	free( s );
}

// -------------------------------------------------------------------------
bool isemptyStack( const_Stack s )
{
	return ( s->cursize == 0 );
}

// -------------------------------------------------------------------------
void pushStack( Stack s, T x )
{
	if ( s->cursize == s->maxsize ) {
		s->maxsize *= 2;
		s->elements = safe_realloc( s->elements, s->maxsize * sizeof *s->elements );
	}
	s->elements[ s->cursize++ ] = x;
}

// -------------------------------------------------------------------------
T topStack( const_Stack s )
{
	return s->elements[ s->cursize-1 ];
}

// -------------------------------------------------------------------------
void popStack( Stack s )
{
	if (s->cursize>0) s->cursize--;
}

// -------------------------------------------------------------------------
int sizeStack( const_Stack s )
{
	return s->cursize;
}

// =========================================================================
// Iterators
// =========================================================================
// Definition of opaque type
struct iter {
	const_Stack base;
	int scan;
};

// -------------------------------------------------------------------------
Iter newIter( const_Stack s )
{
	Iter si = safe_malloc( sizeof *si );
	si->base = s;
	si->scan = 0;
	return si;
}

// -------------------------------------------------------------------------
void freeIter( Iter si )
{
	free( si );
}

// -------------------------------------------------------------------------
bool hasNextIter( const_Iter si )
{
	return si->scan < si->base->cursize ;
}

// -------------------------------------------------------------------------
T nextIter( Iter si )
{
	return si->base->elements[ si->scan++ ];
}
