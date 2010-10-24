/***************************************************************************
 *   Copyright (C) 2007 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "graph.h"
#include "util.h"

// -----------------------------------------------------------------------
// structure definitions
// -----------------------------------------------------------------------
// graph
struct graph {
  int num_nodes;
  Elist* adj;			// array of adjacency lists
};

// edge
struct edge {
  int tail;
  int head;
  int weight;
};

// edge list
struct elist {
  bool owner;			// true if list owns the edges on it
  Ecell head;
  Ecell tail;
};

// edge list cell
struct ecell {
  const_Edge e;
  Ecell next;
};

// iterator over edge list
struct iter_elist {
  Ecell cur;
};

// -----------------------------------------------------------------------
// graph functions
// -----------------------------------------------------------------------
Graph newGraph( int n )	// creates n node graph with no edges
{
  Graph g = safe_malloc( sizeof *g );
  g->num_nodes = n;
  g->adj = safe_malloc( n * sizeof(Elist) ); // array of length n
  // create adjacency lists
  for (int k=0; k < g->num_nodes; k++) 
    g->adj[k] = newElist( true );
  return g;
}

void freeGraph( Graph g )
{
  // free adjacency lists
  for (int k=0; k < g->num_nodes; k++) freeElist( g->adj[k] );

  // free the graph
  free( g->adj );
  free( g );
}

void printGraph( const_Graph g )
{
  printf( "Graph has %i nodes\n", g->num_nodes );
  for (int k=0; k<g->num_nodes; k++) {
    printf( "%i:", k );
    printElist( g->adj[k] );
  }
}

int numNodesGraph( const_Graph g ) // return # nodes of graph
{
  return g->num_nodes;
}

void insertGraph( Graph g, const_Edge e ) // adds edge to graph
{
  int tail = tailEdge( e );
  pushBackElist( g->adj[ tail ], e );
}

Elist getAdjlistGraph( Graph g, int n ) // return adj list of node n
{
  return g->adj[ n ];
}


// -----------------------------------------------------------------------
// edge functions
// -----------------------------------------------------------------------
Edge newEdge( int tail, int head, int weight )
{
  Edge e = safe_malloc( sizeof *e );
  e->tail = tail;
  e->head = head;
  e->weight = weight;
  return e;
}

void freeEdge( Edge e )
{
  free( e );
}

void printEdge( const_Edge e )
{
  printf( "(%i, %i, %i)", e->tail, e->weight, e->head );
}

int tailEdge( const_Edge e )
{
  return e->tail;
}

int headEdge( const_Edge e )
{
  return e->head;
}

int weightEdge( const_Edge e )
{
  return e->weight;
}


// -----------------------------------------------------------------------
// edge list functions
// -----------------------------------------------------------------------
// owner flag is true if the Elist object owns the edges it contains
Elist newElist( bool owner )
{
  Elist p = safe_malloc( sizeof *p );
  p->owner = owner;
  p->head = p->tail = NULL;
  return p;
}

void freeElist( Elist p )
{
  if (p == NULL) return;
  Ecell scan = p->head;
  Ecell next;
  while (scan != NULL) {
    next = scan->next;
    if ( p->owner ) freeEdge( (Edge)scan->e );
    freeEcell( scan );
    scan = next;
  }
  free( p );
}

void printElist( const_Elist p )
{
  IterElist ie = newIterElist( p );
  while (hasNextIterElist( ie )) {
    printf( " " );
    printEdge( nextIterElist( ie ) );
  }
  freeIterElist( ie );
  printf( "\n" );
}

void pushElist( Elist p, const_Edge e )
{
  Ecell ec = newEcell( e );

  if ( p->head == NULL ) {	// first edge
    p->head = p->tail = ec;
  }
  else {
    ec->next = p->head;
    p->head = ec;
  }
}

void pushBackElist( Elist p, const_Edge e )
{
  Ecell ec = newEcell( e );

  if ( p->head == NULL ) {	// first edge
    p->head = p->tail = ec;
  }
  else {
    p->tail->next = ec;
    p->tail = ec;
    ec->next = NULL;
  }
}

bool isemptyElist( Elist p )
{
  return p->head == NULL;
} 

const_Edge popElist( Elist p )
{
  if ( p->head == NULL ) 
    fatal( "Attempt to pop from empty elist" );

  Ecell ec = p->head;
  p->head = ec->next;
  const_Edge e = ec->e;
  freeEcell( ec );
  return e;
}

// -----------------------------------------------------------------------
// edge list cell functions
// -----------------------------------------------------------------------
Ecell newEcell( const_Edge e )
{
  Ecell c = safe_malloc( sizeof *c );
  c->e = e;
  c->next = NULL;
  return c;
}

void freeEcell( Ecell c )
{
  free( c );
}

// -----------------------------------------------------------------------
// iterator over edge list
// -----------------------------------------------------------------------
IterElist newIterElist( const_Elist p ) // create iterator over edge list
{
  IterElist ie = safe_malloc( sizeof *ie );
  ie->cur = p->head;
  return ie;
}

void freeIterElist( IterElist ie ) //free iterator
{
  free( ie );
}


/* test if iterator has next element */
bool hasNextIterElist( const_IterElist ie )
{
  return ie->cur != NULL;
}


/* advance iterator to next element and return it */
const_Edge nextIterElist( IterElist ie )
{
  const_Edge e = ie->cur->e;
  ie->cur = ie->cur->next;
  return e;
}


