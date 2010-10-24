/***************************************************************************
 *   Copyright (C) 2007 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "flexbuf.h"
#include "dijkstra.h"
#include "graph.h"
#include "util.h"

// -------------------------------------------------------------------------
int main (int argc, const char* argv[]) {
  
  if ( argc != 2 ) fatal( "usage: %s file", argv[0] );

  FILE* in = fopen( argv[1], "r" );
  if (in == NULL) fatal( "Can't open '%s' for reading", argv[1] );
  

  // read graph file
  // first line has number of nodes
  // remainder have form: u v1 w1 ... vk w1
  // where (u, 1), ... , (u, k) are edges of weights w1, ..., wk respectively

  Flexbuf fb = newFlexbuf();

  // get number of nodes
  int len = fgetlineFlexbuf( fb, in );
  if ( len==0 ) fatal( "empty file" );
  int num_nodes;
  int n =  sscanf( toStringFlexbuf( fb ), "%i", &num_nodes );
  if ( n != 1 || num_nodes <= 0 )
    fatal( "bad or missing graph size on first line" );

  // create graph
  Graph g = newGraph( num_nodes );

  // get the edges  
  while ( (len = fgetlineFlexbuf( fb, in )) > 0 ) {
    const char* buf = toStringFlexbuf( fb );
    int tail;
    int head;
    int weight;
    int bp;
    n = sscanf( buf, "%i%n", &tail, &bp );
    buf += bp;
    if (n != 1) continue;
    if (tail < 0 || tail >= num_nodes) {
      printf( "Source node %i does not exist -- line ignored\n", tail );
      continue;
    }
    for (;;) {
      n = sscanf( buf, "%i%i%n", &weight, &head, &bp);\
      buf += bp;
      if (n != 2) break;	// go on to next line
      if (head < 0 || head >= num_nodes) {
	printf( "Destination node %i does not exist -- edge ignored\n", head );
	continue;
      }
      insertGraph( g, newEdge( tail, head, weight ) );
    }
  }
  fclose( in );
  freeFlexbuf( fb );

  printGraph( g );


  // find shortest path from first to last node
  Elist p = shortestPathGraph( g, 0, num_nodes-1 );
  if ( p==NULL ) 
    printf( "There is no path from node %i to node %i\n", 0, num_nodes-1 );
  else {
    printf( "The shortest path from node %i to node %i is:\n", 0, num_nodes-1 );
    printElist( p );
    freeElist( p );
  }

  // clean up
  //  freeElist( p );
  freeGraph( g );
}
