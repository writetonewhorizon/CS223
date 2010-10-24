// Michael J. Fischer
// CPSC 223b, Spring 2008
// Problem set 9: Huffman code

#include <stdlib.h>
#include "bitstring.h"
#include "util.h"
#include "ibitstream.h"
#include "codetree.h"

//-------------------------------------------------------------------
int main (int argc, const char * argv[]) 
{
  if (argc!=4) fatal( "usage: %s codefile input output", argv[0] );
  Codetree ctree = newCodetreeFromFile( argv[1] );
  if (ctree == NULL) fatal( "Can't read codetable file \"%s\"", argv[1] );
  FILE* in = fopen( argv[2], "r" );
  if (in == NULL) fatal( "Can't open input file \"$s\" for reading", argv[2] );
  FILE* out = fopen( argv[3], "w" );
  if (out == NULL) fatal( "Can't open output file \"$s\" for writing", argv[3] );
 
  // main decoding loop
  Ibitstream ibs = openIbitstream( in );
  int bit;
  Walker scan = newWalker( ctree );
  while ( (bit=getIbitstream( ibs )) != EOF ) {
    if ( !toSonWalker( scan, bit ) ) fatal( "Corrupted encoded file\n" );
    if ( atLeafWalker( scan ) ) {
      fputc( getValueWalker( scan ), out );
      toRootWalker( scan );
    }
  }

  // clean up
  freeWalker( scan );
  fclose(out);
  fclose(in);
  closeIbitstream( ibs );
  freeCodetree( ctree );
}
