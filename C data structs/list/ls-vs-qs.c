/***************************************************************************
 *   Copyright (C) 2006, 2007, 2008 by Michael Fischer                     *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

// -------------------------------------------------------------------------
//   Linked list sort program
//   Sorts a randomly generated linked list of number
//   Copies the list to an array and sorts again using qsort
//   Prints out time for each sort
//
//   usage:  listsort len
//     where len is the length of list to generate
// -------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>

#include "list.h"
#include "util.h"

// ----------------------------------------------------------------
// Global constant
const char* listsort_version;

// ----------------------------------------------------------------
// local prototypes */
static void runTest(int len);
static void runSortList(List li);
static void runQsort(int size, int* table);
static int compar(const void* xp, const void* yp);
static void printArray(int* x, int len);

// ----------------------------------------------------------------
// Process command line arg and run test

int main(int argc, char *argv[]) {
	// Get desired list length as command line argument
	if (argc < 2)
		fatal("usage: %s size", argv[0]);
	int len = atoi(argv[1]);
	runTest(len);
	printf( "Goodbye!\n" );
}

// ----------------------------------------------------------------
// Generates, sorts, and prints a list of random integers

static void runTest(int len) {
	// Generate random list of given length.
	// Use time of day as seed for random number generator.
	List li = randList(len, time(NULL) );

	// Copy list to array
	int* table = safe_malloc(len*sizeof(int));
	exportList(li, len, table);

	// Print banner
	printf("Comparison of sorting between list mergesort (%s) and qsort\n", listsort_version);
	clock_t ticks_per_sec = sysconf( _SC_CLK_TCK);
	printf("1 clock tick = %g milliseconds\n", 1000.0/ticks_per_sec);

	// Run tests
	printf("--------------------------------------------\n"
		"Sorting with list mergesort (%s)\n"
		"--------------------------------------------\n",
		listsort_version);
	runSortList(li);

	printf("--------------------------------------------\n"
		"Sorting with qsort\n"
		"--------------------------------------------\n");
	runQsort(len, table);

	// Clean up
	free(table);
	freeList(li);
}

// ----------------------------------------------------------------
// Run and time sortList()

static void runSortList(List li) {
	struct tms start, finish; // OS-specific time structures

	// Print list before sorting
	printf("List before sorting:\n");
	printList(li);

	// Sort and time it
	times( &start); // get process times before
	sortList(li);
	times( &finish); // get process times after
	double runtime = finish.tms_utime - start.tms_utime;

	// Print result
	printf("\nSorting completed in %g user cpu clock ticks\n", runtime);
	printf("\nList after sorting:\n");
	printList(li);
}

// ----------------------------------------------------------------
// Run and time qsort()

static void runQsort(int len, int* table) {
	struct tms start, finish; // OS-specific time structures

	// Print array before sorting
	printf("Array before sorting:\n");
	printArray(table, len);

	// sort and time it
	times( &start); // get process times before
	qsort(table, len, sizeof(int), compar);
	times( &finish); // get process times after
	double runtime = finish.tms_utime - start.tms_utime;

	// Print reuslt
	printf("\nQsort completed in %g user cpu clock ticks\n", runtime);

	// Print array after sorting
	printf("\nArray after sorting:\n");
	printArray(table, len);
}

// ----------------------------------------------------------------
// Comparison function for use by qsort

static int compar(const void* xp, const void* yp) {
	const int x = *(int*)xp;
	const int y = *(int*)yp;
	return (x<y) ? -1 : (x==y) ? 0 : 1;
}

// ----------------------------------------------------------------
// prints abbreviated version of array

#define LINESIZE 10
static void printArray(int* x, int len) {
	int left = len;

	printf("  Number of elements: %d\n", len);
	if (left > 2*LINESIZE) {
		printf("  Printing only first and last %d elements of array\n",
				LINESIZE);
	}

	// Print up to first LINESIZE elements of list
	printf("  ");
	for (int i=0; i<LINESIZE && left>0; i++, left--)
		printf(" %4d", x[i]);
	printf("\n");

	// Print line of dots if more than LINESIZE remain
	if (left > LINESIZE)
		printf("   ...\n");

	// Skip to last LINESIZE elements of list
	if (left > LINESIZE)
		left = LINESIZE;

	// Print remainder of list
	if (left > 0) {
		printf("  ");
		for (int i=len-left; i<len; i++) {
			printf(" %4d", x[i]);
		}
		printf("\n");
	}
}

