/*
	Created by: Douglas von Kohorn
	Course: CS223
	Term: Spring 2008
	Problem Set #6
*/

#include <stdio.h>
#include "stack.h"
#include "util.h"

#define INITIAL_STACK_SIZE 10

// -------------------------------------------------------------------------
// definition of struct stack
struct stack {
	int* elements;
	int cursize;
	int maxsize;
};

// -------------------------------------------------------------------------
Stack newStack(void) {
	Stack s = safe_malloc( sizeof(struct stack) );
	s->elements = safe_malloc( INITIAL_STACK_SIZE * sizeof(int) );
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
bool isemptyStack( Stack s )
{
	return ( s->cursize == 0 );
}

// -------------------------------------------------------------------------
void pushStack(Stack s, int x) {
	if (s->cursize == s->maxsize) {
		s->maxsize *= 2;
		s->elements = safe_realloc( s->elements, s->maxsize * sizeof(int) );
	}
	s->elements[ s->cursize++ ] = x;
}

// -------------------------------------------------------------------------
int topStack(Stack s) {
	if (s->cursize == 0)
		fatal( "Attempt to fetch top of empty stack" );
	return s->elements[ s->cursize-1 ];
}

// -------------------------------------------------------------------------
void popStack(Stack s) {
	if (s->cursize == 0)
		fatal( "Attempt to pop an empty stack" );
	if (s->cursize>0)
		s->cursize--;
}

// -------------------------------------------------------------------------
void printStack(Stack s) {
	int k;
	for (k=0; k < s->cursize; k++) {
		printf( " %i", s->elements[ k ] );
	}
	printf("\n");
}
