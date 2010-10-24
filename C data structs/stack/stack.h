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

/* prototypes */
Stack newStack( void );
void  freeStack( Stack );
bool  isemptyStack( Stack );
void  pushStack( Stack, int );
int   topStack( Stack );
void  popStack( Stack );
void  printStack( Stack );

#endif
