/***************************************************************************
 *   Copyright (C) 2006, 2007, 2008 by Michael Fischer                     *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

//  Simple driver for partially testing stack.c

#include <stdio.h>
#include "stack.h"
#include "util.h"

// Specialize generic stack to stack of int*
static void freeInt( void* element );
static void printInt( const void* element );
static const ElementDescriptor ed = { freeInt, printInt };

// -------------------------------------------------------------------------
int main(int argc, const char * argv[])
{	
	Stack s = newStack( &ed );
	printf( "Enter stack commands: +num for push, - for pop, . to quit\n" );
	char command;
	int arg;
	do {
		if (scanf( "%c", &command)!=1) fatal("Can't read command byte" );
		switch (command) {
		case '+':
			if (scanf( "%d", &arg)!=1) fatal("Can't read number to push" );
			int* argp = safe_malloc( sizeof(int) );
			*argp = arg;
			pushStack(s, argp);
			break;
		case '-':
			if (isemptyStack(s) ) {
				printf( "Can't pop -- stack is empty\n" );
			} else {
				popStack(s);
			}
			break;
		default:
			continue;
		}
		printStack(s);
	} while (command != '.');
	
	freeStack(s);
	printf( "Goodbye!\n" );
}

// -------------------------------------------------------------------------
static void freeInt( void* element )
{
	free( element );
}

// -------------------------------------------------------------------------
static void printInt( const void* element )
{
	int x = *(int*)element;
	printf( " %i", x);
}
