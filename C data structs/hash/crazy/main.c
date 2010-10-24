/***************************************************************************
 *   Copyright (C) 2006, 2007, 2008 by Michael Fischer                     *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

// Test program for generic symbol table.
// This program creates a table of "Record" structures, defined by the
// module "record".
// A Record has two string fields: key and value, initialized by newRec().
// The generic symbol table uses the element-specific functions described
// by the constant recordDesc.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "symtab.h"
#include "record.h"

// -------------------------------------------------------------------------
// Element descriptor
static const ElementDesc recordDesc = { 
		(FreeElementFun) freeRec,	// free a data record
		(KeyFun) keyRec,			// return key string embedded in record
		(PrintElementFun) printRec	// print record
};

// -------------------------------------------------------------------------
int main(int argc, const char * argv[]) {
	char key[100];
	char valbuf[100];
	char command;
	bool quit=false;
	Symtab table = newSymtab( &recordDesc);
	printf("Symbol table test program\n");
	do {
		printf("Command (i key val; l key; p print; q quit): ");
		if (scanf(" %c", &command)!=1)
			break;
		switch (toupper(command)) {
		case 'I':
			quit = (scanf("%99s %99s", key, valbuf) != 2);
			if (quit)
				break;
			insertSymtab(table, newRec(key, valbuf));
			break;
		case 'L':
			quit = (scanf("%99s", key)!=1);
			if (quit)
				break;
			const_Record rec = lookupSymtab(table, key);
			if (rec==NOT_FOUND)
				printf("\"%s\" not found in table\n", key);
			else
				printRec(rec);
			break;
		case 'P':
			printSymtab(table);
			break;
		case 'Q':
			quit=true;
		}
	} while ( !quit);

	freeSymtab(table);
	printf("Goodbye!\n");
}
