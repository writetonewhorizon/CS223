/*created by: Douglas von Kohorn
PS9
*/
/***************************************************************************
 *   Copyright (C) 2006--2008 by Michael Fischer                           *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#ifndef HEAP_H
#define HEAP_H

// type definitions
typedef struct heap* Heap;
typedef const struct heap* const_Heap;
typedef int (*comp_fn) (void*, void*);
typedef void (*heap_fn)( const void*, void*);

// prototypes
Heap newHeap( comp_fn );
void freeHeap( Heap );
bool isEmptyHeap( const_Heap );
void insertHeap( Heap, void* );
void* deleteMinHeap( Heap );
void mapHeap( heap_fn, const_Heap, void* );
#endif
