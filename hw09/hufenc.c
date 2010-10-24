/*created by: Douglas von Kohorn
PS9
*/

#include <stdlib.h>
#include "bitstring.h"
#include "codetree.h"
#include "codetable.h"
#include "util.h"
#include "obitstream.h"
#include "heap.h"
#include "hufenc.h"


static int comp( void* p, void* q ) 
{
	int a = ((Node)p)->weight;
	int b = ((Node)q)->weight;
	return (a==b) ? 0 : (a<b) ? -1 : 1;
}
void print_element( const void* node, void* clientData )
{
	printf( "%d | %c\n", ((Node)node)->weight, ((Node)node)->value );
}

//-------------------------------------------------------------------
int main (int argc, const char * argv[]) 
{
	if (argc!=3) fatal( "usage: %s codefile input output", argv[0] );
	FILE* in = fopen( argv[1], "r" );
	if (in == NULL) fatal( "Can't open input file \"$s\" for reading", argv[1] );
	FILE* out = fopen( argv[2], "w" );
	if (out == NULL) fatal( "Can't open output file \"$s\" for writing", argv[2] );
	
	//main encoding loop
	Obitstream obs = openObitstream( out );
	int c;
	Node key;
	int freqTable[256];
	Heap heap = newHeap(comp);
	bool empty = false;

	if(fgetc(in) == EOF) empty = true;
	rewind(in);

	if(!empty)
	{
		//get frequencies and rewind
		for(int j=0;j<256;j++) freqTable[j]=-1;
		while ( (c=fgetc(in)) != EOF )
		{
			freqTable[c] += 1;
		}
		rewind(in);
	
		//create nodes for used symbols
		int numTimes = 0;
		for(int j=0;j<256;j++)
		{
			if(freqTable[j] >= 0)
			{
				numTimes++;
				key = newNode();
				key->weight = freqTable[j]+1;
				key->value = j;
			insertHeap(heap,key);
			}
		}

	
		//insert dummy to avoid degenerative one character case
		key = newNode();
		key->weight = 100;
		key->value = 0;
		insertHeap(heap,key);
	
//		mapHeap(print_element,heap,NULL);
//		printf("\n");
	
		//use min heap to create Huffman tree
		for(int i=0;i<numTimes;i++)
		{
			Node first = (Node)deleteMinHeap(heap);
			Node second = (Node)deleteMinHeap(heap);
	
			Node root = newNode();
			root->son[0] = first;
			root->son[1] = second;
			root->weight = first->weight + second->weight;
	
			insertHeap(heap,root);
		}
	
//		mapHeap(print_element,heap,NULL);
//		printf("\n");
	
	
		//generate a codetree from Node, and a codetable from codetree
		Codetree tree = newCodetreeFromNode((Node)deleteMinHeap(heap));
	//	fprintCodetree(out,tree);
	
		Codetable table = newCodetableFromCodetree(tree);
	//	printCodetable(table);
	
		//write serialized codetree to file
		writeCodetree(tree,obs);
	
		//use codetable to write encoded file
		while ( (c=fgetc(in)) != EOF ) putsObitstream(obs,getCodeword(table,c));
	
// 		printf("\n%i | %i | %i | ",numBits,numLeft,8-numLeft);
// 		fprintBitstring(stdout,string);
// 		printf("\n");

		freeCodetree(tree);
		freeCodetable(table);
	}

	//clean up
	freeHeap(heap);
	closeObitstream( obs );
	fclose(out);
	fclose(in);
}

//serialize codetree
void writeCodetree(Codetree ctree, Obitstream obs) {
	Walker scan = newWalker(ctree);
	Bitstring path = newBitstring();

	path = walkTree(scan, path);
	fprintBitstring(stdout,path);
	putsObitstream(obs,path);

	freeWalker(scan);
	freeBitstring(path);
}

// Recursive walk tree function "helper" function
static Bitstring walkTree(Walker scan, Bitstring path) {
	if (atLeafWalker(scan) ) {
		pushBackBitstring(path,1);
		byte value = getValueWalker(scan);
		Bitstring byteValue = newBitstringFromBytes(8,&value);
		BitstringIter iter = newBitstringIter(byteValue);
		while(hasNextBitstringIter(iter)) pushBackBitstring(path,nextBitstringIter(iter));
		freeBitstring(byteValue);
		freeBitstringIter(iter);
	} else {
		pushBackBitstring(path, 0);
		for (int b=0; b<2; b++) {
			Walker scanb = newWalkerCopy(scan);
			if ( !toSonWalker(scanb, b) )
			{
				fatal("Invalid code tree -- non-leaf lacks son[b]");
			}
			walkTree(scanb, path);
			freeWalker(scanb);
		}
	}

	return path;
}
