/***************************************************************************
 *   Copyright (C) 2008 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

// element type
typedef void* T;

// stack
typedef struct stack* Stack;
typedef const struct stack* const_Stack;

// prototypes
Stack newStack( void );
void  freeStack( Stack );
bool  isemptyStack( const_Stack );
void  pushStack( Stack, T );
T     topStack( const_Stack );
void  popStack( Stack );
int   sizeStack( const_Stack );

// iterator
typedef struct iter* Iter;
typedef const struct iter* const_Iter;

// prototypes
Iter  newIter( const_Stack );
void  freeIter( Iter );
bool  hasNextIter( const_Iter );
T     nextIter( Iter );

#endif
