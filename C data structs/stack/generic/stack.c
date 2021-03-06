/***************************************************************************
 *   Copyright (C) 2006, 2007, 2008 by Michael Fischer                     *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#include <stdio.h>
#include "stack.h"
#include "util.h"

#define INITIAL_STACK_SIZE 10

// -------------------------------------------------------------------------
// definition of struct stack
struct stack {
	void** elements;
	int cursize;
	int maxsize;
};

// -------------------------------------------------------------------------
Stack newStack(void) {
	Stack s = safe_malloc( sizeof(struct stack) );
	s->elements = safe_malloc( INITIAL_STACK_SIZE * sizeof(void*) );
	s->cursize = 0;
	s->maxsize = INITIAL_STACK_SIZE;
	return s;
}

// -------------------------------------------------------------------------
void freeStack(Stack s) {
	free( s->elements );
	free( s );
}

// -------------------------------------------------------------------------
bool isemptyStack( const_Stack s )
{
	return ( s->cursize == 0 );
}

// -------------------------------------------------------------------------
void pushStack( Stack s, void* x ) {
	if (s->cursize == s->maxsize) {
		s->maxsize *= 2;
		s->elements = safe_realloc( s->elements, s->maxsize * sizeof(void*) );
	}
	s->elements[ s->cursize++ ] = x;
}

// -------------------------------------------------------------------------
void* topStack( const_Stack s ) {
	if (s->cursize == 0)
		fatal( "Attempt to fetch top of empty stack" );
	return s->elements[ s->cursize-1 ];
}

// -------------------------------------------------------------------------
void popStack( Stack s ) {
	if (s->cursize == 0)
		fatal( "Attempt to pop an empty stack" );
	if (s->cursize>0)
		s->cursize--;
}

// -------------------------------------------------------------------------
void printStack( const_Stack s, PrintElement pe ) {
	int k;
	for (k=0; k < s->cursize; k++) {
		pe( s->elements[ k ] );
	}
	printf("\n");
}
