/***************************************************************************
 *   Copyright (C) 2006, 2007, 2008 by Michael Fischer                     *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

// Linked list implementation of generic stack

#include <stdio.h>
#include "stack.h"
#include "util.h"

#define INITIAL_STACK_SIZE 10

// -------------------------------------------------------------------------
// Private type 
typedef
struct cell {
	void* element;
	struct cell* next;
} *Cell;

// Definition of struct stack
struct stack {
	Cell head;
	int size;
};

// -------------------------------------------------------------------------
// Prototypes for private functions
static Cell new_cell( void* x, Cell nx );

// -------------------------------------------------------------------------
Stack newStack(void) {
	Stack s = safe_malloc( sizeof(struct stack) );
	s->head = NULL;
	s->size = 0;
	return s;
}

// -------------------------------------------------------------------------
void freeStack(Stack s) {
	Cell scan = s->head;
	Cell cur;
	while (scan != NULL) {
		cur = scan;
		scan = scan->next;
		free(cur);
	}
	free( s );
}

// -------------------------------------------------------------------------
bool isemptyStack( const_Stack s )
{
	return ( s->head == NULL );
}

// -------------------------------------------------------------------------
void pushStack( Stack s, void* x ) {
	s->head = new_cell( x, s->head );
	s->size++;
}

// -------------------------------------------------------------------------
void* topStack( const_Stack s ) {
	return s->head->element;
}

// -------------------------------------------------------------------------
void popStack( Stack s ) {
	Cell old = s->head;
	if (old != NULL) {
		s->head = old->next;
		free( old );
		s->size--;
	}
}

// -------------------------------------------------------------------------
void printStack( const_Stack s, PrintElement pe ) {
	Cell p;
	for (p=s->head; p!=NULL; p=p->next) {
		pe( p->element );
	}
	printf("\n");
}

// -------------------------------------------------------------------------
static Cell new_cell( void* x, Cell nx )
{
	Cell c = safe_malloc( sizeof(struct cell) );
	c->element = x;
	c->next = nx;
	return c;
}


