/***************************************************************************
 *   Copyright (C) 2007 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdbool.h>

// -----------------------------------------------------------------------
// Opaque types
// -----------------------------------------------------------------------
// graph
typedef struct graph* Graph;
typedef const struct graph* const_Graph;

// edge
typedef struct edge* Edge;
typedef const struct edge* const_Edge;

// edge list
typedef struct elist* Elist;
typedef const struct elist* const_Elist;

// edge list cell
typedef struct ecell* Ecell;
typedef const struct ecell* const_Ecell;

// iterator over edge list
typedef struct iter_elist* IterElist;
typedef const struct iter_elist* const_IterElist;


// -----------------------------------------------------------------------
// Graph functions
// -----------------------------------------------------------------------
Graph newGraph( int n );	// creates n node graph with no edges
void  freeGraph( Graph g );
void  printGraph( const_Graph g );
int   numNodesGraph( const_Graph g ); // return # nodes of graph
void  insertGraph( Graph g, const_Edge e ); // adds edge to graph
Elist getAdjlistGraph( Graph g, int n ); // returns adj list of node n

// -----------------------------------------------------------------------
// Edge functions
// -----------------------------------------------------------------------
Edge newEdge( int tail, int head, int weight );
void freeEdge( Edge e );
void printEdge( const_Edge e );
int  tailEdge( const_Edge e );	// returns number of vertex at tail of e
int  headEdge( const_Edge e );	// returns number of vertex at head of e
int  weightEdge( const_Edge e );  // returns edge label of e

// -----------------------------------------------------------------------
// Edge list functions
// -----------------------------------------------------------------------
Elist newElist( bool owner );
void  freeElist( Elist p );
void  printElist( const_Elist p );
void  pushElist( Elist p, const_Edge e );		// put e at front of p
void  pushBackElist( Elist p, const_Edge e );	// put e at back of p
bool  isemptyElist( Elist p );
const_Edge popElist( Elist p );	// remove and return edge at front of p

// -----------------------------------------------------------------------
// edge list cell functions
// -----------------------------------------------------------------------
Ecell newEcell( const_Edge e );
void freeEcell( Ecell c );

// -----------------------------------------------------------------------
// Iterator over edge list
// -----------------------------------------------------------------------
IterElist newIterElist( const_Elist ie );	// create iterator over edge list
void      freeIterElist( IterElist ie ); 	//free iterator

// Test if iterator has next element
bool hasNextIterElist( const_IterElist ie );

// Advance iterator to next element and return it
const_Edge nextIterElist( IterElist ie );

#endif
