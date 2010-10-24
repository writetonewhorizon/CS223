/*
	Created by: Douglas von Kohorn
	Course: CS223
	Term: Spring 2008
	Problem Set #7
*/

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
