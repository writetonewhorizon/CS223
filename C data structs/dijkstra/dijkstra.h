/***************************************************************************
 *   Copyright (C) 2007 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include <stdbool.h>
#include "graph.h"

// -----------------------------------------------------------------------
// dijkstra functions
// -----------------------------------------------------------------------
Elist shortestPathGraph( Graph g, int source, int dest ); // dijkstra

#endif
