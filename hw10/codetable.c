// Michael J. Fischer
// CPSC 223b, Spring 2008
// Problem set 9: Huffman code

/*
 *  codetable.c
 *
 *  Created by Michael Fischer on 2/16/06.
 *  fischer-michael@cs.yale.edu
 *  For use in Yale course CPSC 223b, Spring 2006
 *
 *  Copyright (C) 2006 by Michael Fischer. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "util.h"

#include "codetree.h"
#include "codetable.h"
#include "bitstring.h"

#define CT_SIZE 256

// Define opaque type
struct codetable {
  Bitstring codeword[ CT_SIZE ]; // array of codewords
};

// Codetable functions

//-------------------------------------------------------------------
// Create a new empty code table
Codetable newCodetable( void )
{
  Codetable ct = safe_malloc( sizeof *ct );
  for (int k=0; k<CT_SIZE; k++) ct->codeword[k] = NULL;
  return ct;
}

//-------------------------------------------------------------------
// Create a new code table from data stored in a file
Codetable newCodetableFromFile( const char* fname )
{
  FILE* in = fopen( fname, "r" );
  if (in==NULL) return NULL;

  Codetable ct = newCodetable();
  int k;			/* clear text byte */
  for ( k=0; k<CT_SIZE; k++) {
    Bitstring bs = streamReadBitstring( in );
    if (bs == NULL) break;
    insertCodetable( ct, k, bs );
    freeBitstring( bs );
  }
  fclose( in );
  if (k<CT_SIZE) fatal( "Incomplete code file \"%s\"\n", fname );
  return ct;
}

//-------------------------------------------------------------------
// Free code table
void freeCodetable( Codetable ct )
{
  for (int k=0; k<CT_SIZE; k++) {
    if ( ct->codeword[k] != NULL ) freeBitstring( ct->codeword[k] );
  }
  free( ct );
}

//-------------------------------------------------------------------
// Insert a new (clear, codeword) pair into a code table
void insertCodetable( Codetable ct, byte clear, const_Bitstring codeword )
{
  if ( ct->codeword[ clear ] != NULL ) 
    fatal( "Codeword for byte %hhu already exists", clear );
  ct->codeword[ clear ] = newBitstringCopy( codeword );
}

//-------------------------------------------------------------------
// Get the code word for byte idx
Bitstring getCodeword( const_Codetable ct, int idx )
{
  return ct->codeword[ idx ];
}

//-------------------------------------------------------------------
// Print the code table
void printCodetable( const_Codetable ct ) {
  for (int k=0; k<CT_SIZE; k++) {
    printf( "%3d ", k );
    fprintBitstring( stdout, ct->codeword[k] );
    printf( "\n");
  }
}

//-------------------------------------------------------------------
// Write each of the code words to a file in packed binary format
void fwriteCodetable( const char* fname, Codetable ct )
{
  FILE* out = fopen( fname, "w" );
  if (out == NULL) fatal( "Can't open \"%s\" for writing\n", fname );
  for (int k=0; k<CT_SIZE; k++) {
    streamWriteBitstring( out, ct->codeword[k] );
  }
  fclose( out );
}
