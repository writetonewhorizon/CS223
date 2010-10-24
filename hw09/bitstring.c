/*created by: Douglas von Kohorn
PS9
*/
// Michael J. Fischer
// CPSC 223b, Spring 2008
// Problem set 9: Huffman code

/*
 *  bitstring.c
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
#include "bitstring.h"

/* -------------------------------------------------------------------
 * Bitstring implementation
 *-------------------------------------------------------------------- */

#define INITIAL_BS_SIZE 4	/* initial Bitstring size (bytes) */

/* Bitstring data structure */
struct bitstring {
  int curlen;			/* current length in bits */
  int maxsize;			/* maximum size in bytes  */
  byte* data;			/* packed data bytes */
};

/* Bitstring indexing macros */
#define getbit(bs,k)     (((bs)->data[(k)/8]>>(7-(k)%8))&1)
#define setbit0(bs,k)    (((bs)->data[(k)/8]) &= ~(1<<(7-(k)%8)))
#define setbit1(bs,k)    (((bs)->data[(k)/8]) |=  (1<<(7-(k)%8)))
#define setbit(bs,k,bit) ((bit)?setbit1(bs,k):setbit0(bs,k))

/* Bitstring functions */

/* -------------------------------------------------------------------
 * Default constructor.  Creates Bitstring of length 0
 */
Bitstring newBitstring( void )
{
  Bitstring bs = safe_malloc( sizeof *bs );
  bs->curlen = 0;
  bs->maxsize = INITIAL_BS_SIZE;
  bs->data = safe_malloc( bs->maxsize * sizeof(byte) );
  for (int k=0; k<bs->maxsize; k++) bs->data[k] = 0;
  return bs;
}

/* -------------------------------------------------------------------
 * Creates Bitstring from packed array of bytes
 */
Bitstring newBitstringFromBytes( int len, const byte* buf )
{
  int bytelen = (len+7)/8;

  /* allocate storage */
  Bitstring bs = safe_malloc( sizeof *bs );
  bs->curlen = len;
  bs->maxsize = (8*INITIAL_BS_SIZE > len) ? INITIAL_BS_SIZE : bytelen;
  bs->data = safe_malloc( bs->maxsize * sizeof(byte) );

  /* copy data */
  for (int k=0; k<bytelen; k++) bs->data[ k ] = buf[ k ];
  return bs;
}

/* -------------------------------------------------------------------
 *  Bitstring copy constructor
 */
Bitstring newBitstringCopy( const_Bitstring bs )
{
  Bitstring bs_copy = newBitstringFromBytes( bs->curlen, bs->data );
  return bs_copy;
}

/* -------------------------------------------------------------------
 *  Bitstring destructor
 */
void freeBitstring( Bitstring bs )
{
  free( bs->data );
  free( bs );
}

/* ------------------------------------------------------------------- */
bool isEmptyBitstring( const_Bitstring bs )
{
  return bs->curlen == 0;
}

/* ------------------------------------------------------------------- */
int getLengthBitstring( const_Bitstring bs )
{
  return bs->curlen;
}

/* ------------------------------------------------------------------- */
int popBackBitstring( Bitstring bs )
{
  bs->curlen--;
  return getbit(bs, bs->curlen);
}

/* ------------------------------------------------------------------- */
void pushBackBitstring( Bitstring bs, int bit )
{
  if (bs->curlen == 8*bs->maxsize) { /* string is full - expand */
    int oldmax = bs->maxsize;
    bs->maxsize = 2*oldmax;
    bs->data = safe_realloc( bs->data, bs->maxsize * sizeof(byte) );
    for (int k=oldmax; k<bs->maxsize; k++) bs->data[k] = 0;
  }
  setbit(bs, bs->curlen, bit);
  bs->curlen++;
}

/* -------------------------------------------------------------------
 * Print Bitstring to stream as a sequence of '0' and '1' characters
 */
void fprintBitstring( FILE* out, const_Bitstring bs )
{
  for (int k=0; k<bs->curlen; k++) {
    fprintf( out, "%d", getbit(bs, k) );
  }
}

/* -------------------------------------------------------------------
 * Writes Bitstring to a file in a packed binary format, where
 * first byte is length-1 and remaining bytes are packed data.
 */
void streamWriteBitstring( FILE* out, const_Bitstring bs )
{
  const int maxwrite = (1<<sizeof(byte));
  if (bs->curlen > maxwrite) 
	  fatal( "streamWriteBitstring: Max write length of %d exceeded", maxwrite);
  byte lenbyte = bs->curlen-1;
  size_t nbytes = (bs->curlen+7)/8;
  size_t n;
  n =  fwrite( &lenbyte, sizeof(byte), 1, out );
  n += fwrite( bs->data, sizeof(byte), nbytes, out );
  if (n != nbytes+1) fatal( "Error writing to stream\n" );
}

/* -------------------------------------------------------------------
 * Reads a packed binary Bitstring from a file and returns
 * a new Bitstring object.
 */
Bitstring streamReadBitstring( FILE* in )
{
  byte lenbyte;
  size_t n;
  n = fread( &lenbyte, sizeof(byte), 1, in );
  if (n!=1) return NULL;

  int len = lenbyte+1;
  size_t nbytes = (len+7)/8;

  byte* buf = safe_malloc( len * sizeof(byte) );
  n = fread( buf, sizeof(byte), nbytes, in );
  if (n != nbytes) return NULL;

  Bitstring bs = newBitstringFromBytes( len, buf );
  free( buf );
  return bs;
}


/* -------------------------------------------------------------------
 * Bitstring iterator implementation
 *-------------------------------------------------------------------- */

/* iterator data structure */
struct bs_iter {
  int bit_index;
  const_Bitstring bs;
};

/* iterator functions */

/* ------------------------------------------------------------------- */
BitstringIter newBitstringIter( const_Bitstring bs )
{
  BitstringIter bsi = safe_malloc( sizeof *bsi );
  bsi->bit_index = 0;
  bsi->bs = bs;
  return bsi;
}

/* ------------------------------------------------------------------- */
void freeBitstringIter( BitstringIter bsi ) {
  free( bsi );
}

/* ------------------------------------------------------------------- */
bool hasNextBitstringIter( BitstringIter bsi )
{
  return (bsi->bit_index < bsi->bs->curlen);
}

/* ------------------------------------------------------------------- */
int nextBitstringIter( BitstringIter bsi )
{
  int bit = getbit(bsi->bs, bsi->bit_index);
  bsi->bit_index++;
  return bit;
}
