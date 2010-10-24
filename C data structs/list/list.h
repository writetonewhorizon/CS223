/***************************************************************************
 *   Copyright (C) 2006, 2007, 2008 by Michael Fischer                     *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#ifndef LIST_H
#define LIST_H

/* a linked list */

/*  Opaque types */
typedef struct list* List;
typedef const struct list* const_List;

/* ---------------------------------------------------------------- */
/* prototypes */
List newList(void);
List randList(int len, unsigned seed);
void freeList(List li);
void pushList(int v, List li);
void sortList(List li);
void printList(const_List li);
int exportList(const_List li, int size, int* tbl);

#endif
