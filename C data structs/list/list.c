/***************************************************************************
 *   Copyright (C) 2006, 2007, 2008 by Michael Fischer                     *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "cell.h"
#include "util.h"

#define LINESIZE 10     /* number of elements to print per line */

/* implementation of opaque type */
struct list {
	Cell head;
	int len;
};

/* ================================================================ *
 * Functions on lists                                               *
 * ================================================================ */

/* ----------------------------------------------------------------
 ** Creates and returns new empty list.
 ** Returns NULL if unsuccessful.
 */
List newList(void) {
	List x = safe_malloc(sizeof(*x));
	x->len = 0;
	x->head = NULL;
	return x;
}

/* ----------------------------------------------------------------
 ** Generates random list of 4-digit integers of given length
 */
List randList(int len, unsigned seed) {
	/* create an empty list */
	List x = newList();
	if (x==NULL)
		return x;

	/* generate len random elements and push onto front of x */
	srand(seed);
	for (int i=0; i<len; i++) {
		pushList(rand()%10000, x);
	}
	return x;
}

/* ----------------------------------------------------------------
 ** Frees a list and its attached chain
 */
void freeList(List x) {
	if (x==NULL)
		return;
	freeCells(x->head);
	free(x);
}

/* ----------------------------------------------------------------
 ** puts v at front of list x
 */
void pushList(int v, List x) {
	Cell new = newCell(v, x->head);
	x->head = new;
	x->len++;
}

/* ----------------------------------------------------------------
 ** sorts x using chain merge sort
 */
void sortList(List x) {
	sortFront(x->head, x->len, &x->head);
}

/* ----------------------------------------------------------------
 ** prints abbreviated version of list
 */
void printList(const_List x) {
	int len = x->len;
	Cell scan = x->head;

	printf("  Number of elements: %d\n", len);
	if (len > 2*LINESIZE) {
		printf("  Printing only first and last %d elements of list\n", LINESIZE);
	}

	/* Print up to first LINESIZE elements of list */
	printf("  ");
	for (int i=0; i<LINESIZE && len>0; i++, len--, scan = scan->next)
		printf(" %4d", scan->data);
	printf("\n");

	/* Print line of dots if more than LINESIZE remain */
	if (len > LINESIZE)
		printf("   ...\n");

	/* Skip to last LINESIZE elements of list */
	while (len > LINESIZE) {
		len--;
		scan = scan->next;
	}

	/* Print remainder of list */
	if (len > 0) {
		printf("  ");
		while (scan != NULL) {
			printf(" %4d", scan->data);
			scan = scan->next;
		}
		printf("\n");
	}
}

/* ----------------------------------------------------------------
 ** copies up to size elements of list li to array tbl
 ** returns number of elements copied
 */
int exportList(const_List li, int size, int* tbl) {
	int len = li->len;
	Cell scan = li->head;
	int num = (len <= size ? len : size );
	int k;

	for (k=0; k<num; k++) {
		tbl[k] = scan->data;
		scan = scan->next;
	}
	return num;
}
