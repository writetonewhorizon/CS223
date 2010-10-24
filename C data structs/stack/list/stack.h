/***************************************************************************
 *   Copyright (C) 2006, 2007, 2008 by Michael Fischer                     *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#ifndef _STACK_H
#define _STACK_H

#include <stdbool.h>

typedef
struct stack* Stack;
typedef const struct stack* const_Stack;

typedef
void PrintElement ( const void* );

/* prototypes */
Stack newStack( void );
void  freeStack( Stack );
bool  isemptyStack( const_Stack );
void  pushStack( Stack, void* );
void* topStack( const_Stack );
void  popStack( Stack );
void  printStack( const_Stack, PrintElement );

#endif
