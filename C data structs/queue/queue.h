/***************************************************************************
 *   Copyright (C) 2006, 2007, 2008 by Michael Fischer                     *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef int T;

// Opaque types
typedef struct queue* Queue;
typedef const struct queue* const_Queue;

typedef struct iter* IterQueue;
typedef const struct iter* const_IterQueue;

// Prototypes

// Queue
Queue newQueue( void );
void freeQueue( Queue );
bool isEmptyQueue( const_Queue );
void pushQueue( Queue, T );
T topQueue( const_Queue );
void popQueue( Queue );
int sizeQueue( const_Queue );

// Queue iterator
IterQueue newIterQueue( Queue );
void freeIterQueue( IterQueue );
bool hasNextQueue( const_IterQueue );
T nextQueue( IterQueue );

#endif
