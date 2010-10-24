/***************************************************************************
 *   Copyright (C) 2006, 2007, 2008 by Michael Fischer                     *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#ifndef CELL_H
#define CELL_H

/* public structure */
struct cell {
	int data;
	struct cell* next;
};

/* cell type */
typedef struct cell* Cell;

/* ---------------------------------------------------------------- */
/* prototypes */

Cell newCell(int v, Cell x);
void freeCells(Cell x);
Cell sortFront(Cell x, int len, Cell* yp);
Cell mergeChains(Cell x, Cell y);

#endif
