/*created by: Douglas von Kohorn
PS9
*/
#include <stdlib.h>
#include "bitstring.h"
#include "util.h"
#include "ibitstream.h"
#include "codetree.h"
#include "hufdec.h"

//-------------------------------------------------------------------
int main (int argc, const char * argv[]) 
{
	if (argc!=3) fatal( "usage: %s codefile input output", argv[0] );
	FILE* in = fopen( argv[1], "r" );
	if (in == NULL) fatal( "Can't open input file \"$s\" for reading", argv[1] );
	FILE* out = fopen( argv[2], "w" );
	if (out == NULL) fatal( "Can't open output file \"$s\" for writing", argv[2] );

	Ibitstream ibs = openIbitstream( in );

	//recursively re-create tree
	Codetree ctree = makeTree(ibs);
//	fprintCodetree(stdout,ctree);


	int bit;

	bit = getIbitstream(ibs);

	Walker scan = newWalker( ctree );
	while(bit != EOF)
	{
		if ( !toSonWalker( scan, bit ) ) fatal( "Corrupted encoded file\n" );

		if ( atLeafWalker( scan ) ) 
		{
			fputc( getValueWalker( scan ), out );
			toRootWalker( scan );
		}
		bit = getIbitstream(ibs);
	}

	//clean up
	freeWalker( scan );
	fclose(out);
	fclose(in);
	closeIbitstream( ibs );
	freeCodetree( ctree );
}

Codetree makeTree(Ibitstream ibs)
{
	Codetree temp = newCodetreeFromNode(makeTreeHelper(ibs,newNode()));
	return temp;
}

Node makeTreeHelper(Ibitstream ibs, Node root)
{
	int bit = getIbitstream(ibs);
	if(bit == 0)
	{
		Node leftSon = newNode();
		Node rightSon = newNode();

		leftSon = makeTreeHelper(ibs,leftSon);
		rightSon = makeTreeHelper(ibs,rightSon);

		root->son[0] = leftSon;
		root->son[1] = rightSon;
	} else
	{
		byte value = 0;
		for(int i = 7; i >= 0; i--)
		{
			byte temp1 = 1 << i;
			byte temp2 = getIbitstream(ibs) << i;
			value = value | (temp1 & temp2);
		}
		root->value = value;
	}
	return root;
}
