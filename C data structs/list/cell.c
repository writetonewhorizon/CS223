/***************************************************************************
 *   Copyright (C) 2006, 2007, 2008 by Michael Fischer                     *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "cell.h"
#include "util.h"

// ----------------------------------------------------------------
// Global constant
const char* listsort_version = "unoptimized";

/* ================================================================ *
 * Functions on cells                                                *
 * ================================================================= */

/* ----------------------------------------------------------------
 ** Creates, initializes, and returns new cell.
 ** Returns NULL if unsuccessful.
 */
Cell newCell(int v, Cell x) {
	Cell new = safe_malloc( sizeof(*new));
	new->data = v;
	new->next = x;
	return new;
}

/* ----------------------------------------------------------------
 ** free chain of cells
 */
void freeCells(Cell x) {
	Cell headCell;
	while (x!=NULL) {
		headCell = x;	// point to cell to be freed
		x = x->next;	// advance scanner
		free(headCell);	// free cell
	}
}

/* ================================================================ *
 ** Chain merge sort                                                 *
 ** ================================================================ */

/* ----------------------------------------------------------------
 ** Removes first len cells of x, recursively sorts them, and stores
 ** the result in *yp.
 ** Returns the (unsorted) remainder of original chain.
 */
Cell sortFront(Cell x, int len, Cell* yp) {
	Cell rest;				// unsorted remainder of x

	if (len==0) {			// nothing to remove from x
		rest = x;			// all of x is remainder
		*yp = NULL;			// empty chain is already sorted
	} else if (len==1) {	// remove one cell from x
		rest = x->next;		// remainder is tail of x
		x->next = NULL;		// break chain
		*yp = x; 			// singleton chain is already sorted
	} else { 				// recursive case
		int half = len/2; 	// divide len roughly in two
		Cell x1;			// sorted first half cells of x
		Cell x2;			// sorted next len-half cells of x
		// recursively sort the first two half-length blocks of x
		rest = sortFront(sortFront(x, half, &x1), len-half, &x2);
		// merge resulting sorted parts
		*yp = mergeChains(x1, x2);
	}
	return rest;
}

/* ----------------------------------------------------------------
 ** Destructively merges its two arguments which must be sorted
 ** chains in ascending order and returns the resulting chain.

 Method:  smallest element is repeatedly removed from
 front of x or y and placed at end of new chain rooted
 at dummy header cell using ztail.
 When either x or y is exhausted, the remainder of the
 other chain is appended to the new chain.
 The dummy header is discarded and the remainder of the
 chain is returned.
 */
Cell mergeChains(Cell x, Cell y) {
	struct cell dummy = { 0, NULL }; // initialize fields of dummy cell
	Cell ztail = &dummy;

	// perform merge of x and y
	while (x!=NULL && y!=NULL) {
		if (x->data <= y->data) {
			/* move first cell of x to end of new chain */
			ztail->next = x;
			ztail = x;
			x = x->next;
		} else {
			/* move first cell of y to end of new chain */
			ztail->next = y;
			ztail = y;
			y = y->next;
		}
	}

	// clean up
	// x or y (or both) are now NULL
	// append remaining cells from x or y
	if (x!=NULL)	// x is non-empty
		ztail->next = x;
	else			// ok if y is also empty
		ztail->next = y;

	// return new chain excluding dummy header
	return dummy.next;
}

