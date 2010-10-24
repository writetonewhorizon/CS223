/*
	Created by: Douglas von Kohorn
	Course: CS223
	Term: Spring 2008
	Problem Set #4
*/

#include "wordfreq.h"
#include <stdio.h>
#include "util.h"

int main(int argc, char* argv[])
{
	// check for exactly one command line argument
	if (argc != 2)
	{
		fatal("TOO MANY ARGUMENTS\n", argv[0]);
	}

	// get file name from command line argument vector
	char* infile = argv[1];

	// try to open the file
	printf("Attempting to open file %s for reading\n", infile);
	FILE* in; // defines in to be a stream
	in = fopen(infile, "r");
	if (in == NULL)
	{
		fatal("Failed to open file %s for reading\n", infile);
	}

	// create a new Flex data structure called "cart"
	Flex cart = newFlex();
	
	// put some things into the cart
	for(;;)
	{
		if(fill(cart, in) == EOF) break;
	}

	if(lenFlex(cart) == 0) fatal("Nothing in file, did you do your assignment?");
	else process( cart );
	
	// done with cart, so clean up
	freeFlex( cart );

	fclose(in);

	// announce termination
	printf( "Goodbye!\n" );

	return 0;
}
