// Michael J. Fischer
// CPSC 223b, Spring 2008

#include <stdio.h>
#include "partition.h"

#define SIZE 10		// size of the universe

// Private function prototype
static void testPartition( Part pt );

// ------------------------------------------------------------------------
// Simple driver function to test union-find partition algorithm
int main( void )
{
	printf( "Union-find test program\n"
			"Universe: [0, ..., %i]\n"
			"Commands: u x y - unions together blocks containing x and y\n"
			"          f x   - finds block containing x\n"
			"          p     - print partition\n"
			"          .     - quit\n",
			SIZE-1 );
	
	Part pt = newPart( SIZE );
	testPartition( pt );
	freePart( pt );
	printf( "Goodbye!\n" );
}

// ------------------------------------------------------------------------
static void testPartition( Part pt )
{
	char c;
	int n;
	int x, y, xroot, yroot, newroot;
	int ch;

	for (;;) {
		printf( "Command: ");
		n = scanf( " %c", &c );
		if (n==EOF) break;
		if (c=='.') break;
		switch (c) {
		case 'u':
			n = scanf( "%i%i", &x, &y);
			if (n!=2) break;
			if (x<0 || x >= SIZE || y<0 || y >= SIZE) break;
			xroot = findPart( pt, x );
			yroot = findPart( pt, y );
			newroot = unionPart( pt, xroot, yroot );
			printf( "Union has block id %i\n", newroot );
			break;
		case 'f':
			n = scanf( "%i", &x );
			if (n!=1) break;
			if (x<0 || x >= SIZE) break;
			xroot = findPart( pt, x );
			printf( "%i is in block %i\n", x, xroot );
			break;
		case 'p':
			printPart( pt );
			break;
		default:
			printf( "Unknown command '%c'\n", c);
		}
		// skip remainder of line
		do {
			ch = getchar();
			if (ch == EOF) break;
		} while( ch != '\n' );
	}
}
