// Michael J. Fischer
// CPSC 223b, Spring 2008

#ifndef PARTITION_H_
#define PARTITION_H_

// --------------------------------------------------------
// Partition on the integers {0, ..., n-1}
typedef struct part* Part;
typedef const struct part* const_Part;

// --------------------------------------------------------
// Partition functions
// --------------------------------------------------------

// Create a partition of size num of singleton blocks
Part newPart( int num );

// Destroy partition
void freePart( Part pt );

// Return size of the universe of elements
int sizePart( const_Part pt );

// Find ID of block containing element k
int findPart( const_Part pt, int k );

// Replace blocks k1 and k2 in partition pt by their union
int unionPart( Part pt, int k1, int k2 );

// Print the partition
void printPart( const_Part pt );

#endif /*PARTITION_H_*/
