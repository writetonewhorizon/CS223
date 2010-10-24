// Michael J. Fischer
// CPSC 223b, Spring 2008
// Problem set 9: Huffman code

#include <stdlib.h>
#include "bitstring.h"
#include "codetable.h"
#include "util.h"
#include "obitstream.h"

//-------------------------------------------------------------------
int main (int argc, const char * argv[]) 
{
  if (argc!=4) fatal( "usage: %s codefile input output", argv[0] );
  Codetable ct = newCodetableFromFile( argv[1] );
  if (ct == NULL) fatal( "Can't read codetable file \"%s\"", argv[1] );
  FILE* in = fopen( argv[2], "r" );
  if (in == NULL) fatal( "Can't open input file \"$s\" for reading", argv[2] );
  FILE* out = fopen( argv[3], "w" );
  if (out == NULL) fatal( "Can't open output file \"$s\" for writing", argv[3] );
  
  // main encoding loop
  Obitstream obs = openObitstream( out );
  int c;
  Bitstring bs;
  while ( (c=fgetc(in)) != EOF ) {
    bs = getCodeword( ct, c );
    putsObitstream( obs, bs );
  }

	printCodetable(ct);

  // clean up
  closeObitstream( obs );
  fclose(out);
  fclose(in);
  freeCodetable( ct );
}
