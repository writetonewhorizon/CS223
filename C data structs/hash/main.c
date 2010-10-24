/***************************************************************************
 *   Copyright (C) 2006, 2007 by Michael Fischer                           *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2007                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "symtab.h"
#include "symtab-iter.h"
#include "symtab-map.h"

static void print_pair( const char* key, const void* value, void* clientData );

int main (int argc, const char * argv[]) {
  char key[100];
  char valbuf[100];
  char command;
  bool quit=false;
  symtab table = new_symtab();
  do {
    printf( "Command (i key val; l key; p print; q quit): " );
    scanf( " %c", &command );
    switch( toupper(command) ) {
    case 'I':			/* insert */
      scanf( "%99s %99s", key, valbuf );
      char* newval = malloc( strlen(valbuf)+1 );
      strcpy( newval, valbuf );
      insert( table, key, newval );
      break;
    case 'L':			/* locate */
      scanf( "%99s", key );
      char* value = lookup( table, key );
      if ( value==NOT_FOUND )
        printf( "\"%s\" not found in table\n", key );
      else
        print_pair( key, value, NULL );
      break; 
    case 'P':			/* print */
      printf( "Printing table using iterator\n" );
      symtab_iter it = new_symtab_iter( table );
      while (has_next_symtab_iter( it )) {
        char* key = next_symtab_iter( it );
        char* value = lookup( table, key );
        print_pair( key, value, NULL );
      }
      printf( "\nPrinting table using map function\n" );
      map_symtab( print_pair, table, NULL );
      break;
    case 'Q':
      quit=true;
    }
  } while( !quit );
  
  free_symtab( table );
}

// -----------------------------------------------------
// print key-value pair
static void print_pair( const char* key, const void* value, void* clientData )
{
  printf( "Value of \"%s\" is \"%s\"\n", key, (const char*) value );  
}
