/***************************************************************************
 *   Copyright (C) 2006, 2007, 2008 by Michael Fischer                     *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#include <stdlib.h>
#include "queue.h"

// ------------------------ linked list-based Queue -----------------------

// Private type
typedef
struct cell {
  T element;
  struct cell* next;
} *Cell;

// Definition of opaque structure
struct queue {
  Cell head;
  Cell tail;
  int size;
};

// Private function prototype
static Cell newCell( T x, Cell nx );

// -------------------------------------------------------------
// Public functions
// -------------------------------------------------------------
Queue newQueue( void )
{
  Queue s = malloc( sizeof(struct queue) );
  s->head = NULL;
  s->tail = NULL;
  s->size = 0;
  return s;
}

// -------------------------------------------------------------
void freeQueue( Queue s )
{
  Cell scan = s->head;
  Cell cur;
  while (scan != NULL) {
    cur = scan;
    scan = scan->next;
    free(cur);
  }
  free( s );
}

// -------------------------------------------------------------
bool isEmptyQueue( const_Queue s )
{
  return ( s->head == NULL );
}

// -------------------------------------------------------------
void pushQueue( Queue s, T x )
{
  if (s->tail == NULL) {
    s->head = s->tail = newCell( x, NULL );
  } else {
    s->tail->next = newCell( x, NULL );
    s->tail = s->tail->next;
  }
  s->size++;
}

// -------------------------------------------------------------
T topQueue( const_Queue s )
{
  return s->head->element;
}

// -------------------------------------------------------------
void popQueue( Queue s )
{
  if (s->head != NULL) {
    Cell old = s->head;
    if (s->tail == old) s->tail = NULL;
    s->head = old->next;
    free( old );
    s->size--;
  }
}

// -------------------------------------------------------------
int sizeQueue( const_Queue s )
{
  return s->size;
}

// ----------------------- iterators ---------------------
// -------------------------------------------------------------
struct iter {
  Cell scan;
};

// -------------------------------------------------------------
IterQueue newIterQueue( Queue s )
{
  IterQueue si = malloc( sizeof(struct iter) );
  si->scan = s->head;
  return si;
}

// -------------------------------------------------------------
void freeIterQueue( IterQueue si )
{
  free( si );
}

// -------------------------------------------------------------
bool hasNextQueue( const_IterQueue si )
{
  return si->scan != NULL ;
}

// -------------------------------------------------------------
T nextQueue( IterQueue si )
{
  T x = si->scan->element;
  si->scan = si->scan->next;
  return x;
}

// -------------------------------------------------------------
// Private functions
// -------------------------------------------------------------
static
Cell newCell( T x, Cell nx )
{
  Cell c = malloc( sizeof(struct cell) );
  c->element = x;
  c->next = nx;
  return c;
}
