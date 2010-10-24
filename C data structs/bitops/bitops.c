/***************************************************************************
 *   Copyright (C) 2007 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "util.h"

#define BITSTRING unsigned int
#define N (8*sizeof(BITSTRING))
#define TEST(a) printf( #a "(x)=%d\n", a( x ) )
#define DEBUG(a) ( a )

// prototypes
void printbin( char* before, unsigned x, char* after );
int parity1( BITSTRING x );
int parity2( BITSTRING x );
int parity3( BITSTRING x );
int parity4( BITSTRING x );
int parity5( BITSTRING x );
int parity5a( BITSTRING x, int n );
int parity6( BITSTRING x );
int parity6a( BITSTRING x, int n );
int parity7( BITSTRING x );
int popcount1( BITSTRING x );
int popcount3( BITSTRING x );
int popcount4( BITSTRING x );
int popcount5( BITSTRING x );
int popcount5a( BITSTRING x, int n );
int popcount6( BITSTRING x );
int popcount6a( BITSTRING x, BITSTRING mask, int n );
int popcount7( BITSTRING x );

// Operations for doing population counts and population counts mod 2

// -------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  if (argc != 2) fatal( "usage: %s hex_number", argv[0] );
  unsigned x;
  sscanf( argv[1], "%x", &x );
  //unsigned x = strtol( argv[1], &endptr, 0 );
  printbin( "x=", x, "\n" );
  TEST(parity1);
  TEST(parity2);
  TEST(parity3);
  TEST(parity4);
  TEST(parity5);
  TEST(parity6);
  TEST(parity7);
  TEST(popcount1);
  TEST(popcount3);
  TEST(popcount4);
  TEST(popcount5);
  TEST(popcount6);
  TEST(popcount7);
}

// -------------------------------------------------------------------
void printbin( char* before, unsigned x, char* after )
{
  printf( "%s", before );
  for (int k=N-1; k>=0; k--) {
    printf( "%u", (x >> k) & 1 );
  }
  printf( "%s", after );
}

// -------------------------------------------------------------------
// Compute parity by shifting and XOR
int parity1( BITSTRING x )
{
  int parity = 0;
  for (int k=0; k<N; k++) {
    parity ^= (x >> k) & 1;
  }
  return parity;
}
  
// -------------------------------------------------------------------
// Compute parity by shifting and XOR -- mask only at end
int parity2( BITSTRING x )
{
  int parity = 0;
  for (int k=0; k<N; k++) {
    parity ^= (x >> k);
  }
  return parity & 1;
}

// -------------------------------------------------------------------
// Compute parity by shifting and XOR -- mask only at end
// Stop when x becomes 0
int parity3( BITSTRING x )
{
  int parity = 0;
  while (x != 0) {
    parity ^= x;
    x >>= 1;
  }
  return parity & 1;
}
  
// -------------------------------------------------------------------
// Compute parity by using subtraction trick to turn rightmost
// 1 to 0.
// Stop when x becomes 0.
int parity4( BITSTRING x )
{
  int parity = 0;
  while (x != 0) {
    parity ^= 1;
    x &= (x-1);
  }
  return parity;
}

// -------------------------------------------------------------------
// Compute parity recursively -- linear time
int parity5( BITSTRING x )
{
  return parity5a( x, N ) & 1;
}

// -------------------------------------------------------------------
// Helper function.
// Computes parity of rightmost n bits of x.
int parity5a( BITSTRING x, int n )
{
  if (n==1) return x;

  // Split rightmost n bits of x into two blocks of length n/2 each
  int n2 = n >> 1; 		// n2 = n/2
  BITSTRING x0 = x >> n2;	// left half of length n block of x
  BITSTRING x1 = x;		// right half of length n block of x
  return parity5a( x0, n2 ) ^ parity5a( x1, n2 );
}

// -------------------------------------------------------------------
// Compute parity recursively -- logarithmic time
int parity6( BITSTRING x )
{
  return parity6a( x, N ) & 1;
}

// -------------------------------------------------------------------
// Helper function.
// Computes parity of rightmost n bits of x using parallel XOR
int parity6a( BITSTRING x, int n )
{
  if (n==1) return x;
  // consider block of n rightmost bits of x
  // recurse on XOR of left and right halves of that block
  int n2 = n >> 1; 		// n2 = n/2
  return parity6a( (x >> n2)^x, n2 );
}

// -------------------------------------------------------------------
// Iterative version of parity6
int parity7( BITSTRING x )
{
  int n = N;
  while (n != 1) {
    n >>= 1;
    x ^= (x >> n);
  }
  return x&1;
}

// -------------------------------------------------------------------
// Population count functions
// -------------------------------------------------------------------
// Compute population count by shift and add
int popcount1( BITSTRING x )
{
  int count = 0;
  for (int k=0; k<N; k++) {
    count += (x >> k) & 1;
  }
  return count;
}
  
// -------------------------------------------------------------------
// Compute population count by shift and add,
// stopping when x becomes 0
int popcount3( BITSTRING x )
{
  int count = 0;
  while (x != 0) {
    count += x & 1;
    x >>= 1;
  }
  return count;
}
  
// -------------------------------------------------------------------
// Compute population count by using subtraction trick to turn rightmost
// 1 to 0.
// Stop when x becomes 0.
int popcount4( BITSTRING x )
{
  int count = 0;
  while (x != 0) {
    count++;
    x &= (x-1);
  }
  return count;
}

// -------------------------------------------------------------------
// Compute population count recursively using linear time algorithm
// (Inefficint -- for illustration only.)
int popcount5( BITSTRING x )
{
  return popcount5a( x, N );
}

// -------------------------------------------------------------------
// Helper function
// Compute population count of rightmost n bits
int popcount5a( BITSTRING x, int n )
{
  if (n==1) return x&1;

  // Split rightmost n bits of x into two blocks of length n/2 each
  int n2 = n >> 1; 		// n2 = n/2
  BITSTRING x0 = x >> n2;	// left half of length n block of x
  BITSTRING x1 = x;		// right half of length n block of x
  return popcount5a( x0, n2 ) + popcount5a( x1, n2 );
}

// -------------------------------------------------------------------
// Compute population count recursively in logarithmic time
int popcount6( BITSTRING x )
{
  return popcount6a( x, ~0, N );
}

// View x as consisting of a vector of n-bit blocks.
// Returns a word y consisting of vector of n-bit blocks, where each
// block of y is the population count of the corresponding block of x.
// mask consists of alternating n-bit blocks of all 0's and all 1's
int popcount6a( BITSTRING x, BITSTRING mask, int n )
{
  DEBUG( printf( ">>> popcount6a( 0x%08x, 0x%08x, %d )\n", x, mask, n ) );
  BITSTRING y, y0, y1;

  if (n==1) return x;
  
  int n2 = n >> 1;
  BITSTRING mask2 = (mask << n2) ^ mask;  // flips left half of each block

  y = popcount6a( x, mask2, n2 ); // recursive call
  y0 = y & mask2;                 // get right sub-blocks
  y1 = (y >> n2) & mask2;         // get left sub-blocks and align with right
  y = y0+y1;                      // add them together
  DEBUG( printf( ">>> returning 0x%08x\n", y ) );
  return y;
}

// -------------------------------------------------------------------
// Iterative version of parallel population count

static const BITSTRING mask[5] = {
  0x55555555,
  0x33333333,
  0x0f0f0f0f,
  0x00ff00ff,
  0x0000ffff,
};

int popcount7( BITSTRING x )
{
  int n = 1;
  int k = 0;
  BITSTRING x0, x1;

  while (n != N) {
    x0 = x & mask[k];
    x1 = (x >> n) & mask[k];
    x = x0 + x1;
    n <<= 1;
    k++;
  }
  return x;
}

