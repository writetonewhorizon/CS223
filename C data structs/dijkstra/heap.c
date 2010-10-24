/***************************************************************************
 *   Copyright (C) 2006--2008 by Michael Fischer                           *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "heap.h"
#include "util.h"

#define INITIAL_SIZE 10

// Definition of opaque structure
struct heap {
  Comp_fn comp;			// comparison function
  Free_fn freeNode;		// free function
  int cursize;			// current size of heap
  int maxsize;			// maximum size of heap
  void** node;			// array of heap nodes
};

// navigation macros
#define father(a) ((a)/2)
#define left(a)   (2*(a))
#define right(a)  (2*(a)+1)
#define root      1
#define end(h)    (h->cursize+1) // first available slot

// -------------------------------------------------------------------
// heap constructor
//
Heap newHeap( Comp_fn comp, Free_fn freeNode )
{
  Heap h = safe_malloc( sizeof *h );
  h->comp = comp;
  h->freeNode = freeNode;
  h->cursize = 0;
  h->maxsize = INITIAL_SIZE;
  h->node = safe_malloc( INITIAL_SIZE * sizeof(void*) );
  return h;
}

// -------------------------------------------------------------------
// heap destructor
// 
void freeHeap( Heap h )
{
  for (int k=root; k < end(h); k++) h->freeNode( h->node[ k ] );
  free( h->node );
  free( h );
}

// -------------------------------------------------------------------
// test if heap is empty
// 
bool isEmptyHeap( const_Heap h )
{
  return h->cursize == 0;
}

// -------------------------------------------------------------------
// insert element at end of heap and fixup heap by walk towards root
// 
void insertHeap( Heap h, void* value )
{
  // expand if necessary to accommodate a new node
  if ( end(h) == h->maxsize ) {	// no more available slots
    h->maxsize *= 2;
    h->node = safe_realloc( h->node, h->maxsize * sizeof(void*) );
  }

  // create a hole at end of heap
  int hole = end(h);
  h->cursize++;

  // move hole upwards to place where new value goes
  while (hole != root) {
    // test if value belongs in hole
    int scan = father(hole);    
    if (h->comp( h->node[ scan ], value ) <= 0) // yes
      break;
    // no, move hole up one level
    h->node[ hole ] = h->node[ scan ];
    hole = scan;
  }

  // fill hole with new element
  h->node[ hole ] = value;   
}

// -------------------------------------------------------------------
// remove root element and reinsert last element from heap into hole
// 
void* deleteMinHeap( Heap h )
{
  // safety check
  if ( h->cursize <= 0 ) fatal( "Attempt to delete from empty heap\n" );

  // save return value, creating a hole at the root
  void* minval = h->node[ root ];
  int hole = root;

  // remove last element from tree
  --h->cursize;
  void* value = h->node[ end(h) ];

  // move hole downwards, always filling hole with smaller of two sons.
  //   stop when hole is at place where removed element goes
  for (;;) {
    int lson = left( hole );
    int rson = right( hole );

    // find smaller son, if any
    int smaller = lson;
    if (lson >= end(h)) break; // hole is a leaf
    if (rson < end(h) &&
	h->comp( h->node[ lson ], h->node[ rson ] ) > 0)
      smaller = rson;		// rson exists and is smaller than lson

    // does value go in hole?
    if (h->comp( value, h->node[ smaller ] ) <= 0) // yes
      break;

    // no, move hole down one level
    h->node[ hole ] = h->node[ smaller ];
    hole = smaller;
  }

  // fill hole with previously lasat element
  h->node[ hole ] = value;

  // return min element put aside earlier
  return minval;
}
