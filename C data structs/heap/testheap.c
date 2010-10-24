/***************************************************************************
 *   Copyright (C) 2008 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "heap.h"
#include "util.h"

// -------------------------------------------------------------------------
// Compare two heap elements
static int comp( void* p, void* q ) 
{
  int a = *(int*)p;
  int b = *(int*)q;
  return (a==b) ? 0 : (a<b) ? -1 : 1;
}

// -------------------------------------------------------------------------
// Print a heap element
void print_element( const void* node, void* clientData )
{
  printf( " %d", *(const int*)node );
}

// -------------------------------------------------------------------------
int main (int argc, const char * argv[]) 
{
  int* key;
  char command;
  bool quit=false;
  printf( "Welcome to heap test program\n" );
  Heap h = newHeap( comp );
  do {
    printf( "Command: ('h' for help): " );
    scanf( " %c", &command );
    switch( toupper(command) ) {
    case 'H':			/* help */
      printf( "Commands:\n"
	      "  i num - insert number into heap\n"
	      "  d     - delete minimum element from heap\n"
	      "  p     - print heap\n"
	      "  q     - quit\n" );
      break;
    case 'I':			/* insert */
      key = safe_malloc( sizeof *key );
      scanf( "%d", key );
      insertHeap( h, key );
      break;
    case 'D':			/* delete_min */
      if (isEmptyHeap( h )) {
	printf( "Heap is empty\n" );
      }
      else {
        key = deleteMinHeap( h );
        printf( "%d\n", *key );
        free( key );
      }
      break; 
    case 'P':			/* print */
      mapHeap( print_element, h, NULL );
      printf( "\n" );
      break;
    case 'Q':
      quit=true;
    }
  } while( !quit );
  
  freeHeap( h );
  printf( "Goodbye!\n" );
}
