/***************************************************************************
 *   Copyright (C) 2006, 2007, 2008 by Michael Fischer                     *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "record.h"
#include "util.h"

// -------------------------------------------------------------------------
// Record with two strings
struct record {
	char* name;
	char* val;
};

// -----------------------------------------------------
// Create new record
Record newRec(const char* name, const char* val) {
	Record newrec = safe_malloc( sizeof *newrec);
	newrec->name = safe_malloc(strlen(name)+1);
	strcpy(newrec->name, name);
	newrec->val = safe_malloc(strlen(val)+1);
	strcpy(newrec->val, val);
	return newrec;
}

// ----------------------------------------------------
// Free record
void freeRec(const_Record rec) {
	free(rec->name);
	free(rec->val);
	free( (Record) rec );	// use cast to discard const
}

// ----------------------------------------------------
// Return key field of record
const char* keyRec(const_Record rec) {
	return rec->name;
}

// ----------------------------------------------------
// Print a record
void printRec(const_Record rec) {
	printf("Value of \"%s\" is \"%s\"\n", rec->name, rec->val);
}

