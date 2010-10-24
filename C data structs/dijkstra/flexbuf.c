/***************************************************************************
 *   Copyright (C) 2007 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flexbuf.h"
#include "util.h"

#define INITIAL_CHUNK_SIZE 8

//--------------------------------------------------------------------------
// Definition of opaque type
//--------------------------------------------------------------------------
struct flexbuf {
	int len;	// allocation length
	char* buf;	// storage area
};

//==========================================================================

//--------------------------------------------------------------------------
// Create a new empty flexbuf
//--------------------------------------------------------------------------
Flexbuf newFlexbuf(void) {
	Flexbuf fb = safe_malloc( sizeof(*fb));
	fb->len = 0;
	fb->buf = NULL;
	return fb;
}

//--------------------------------------------------------------------------
// Free a flexbuf
//--------------------------------------------------------------------------
void freeFlexbuf(Flexbuf fb) {
	if (fb->buf != NULL)
		free(fb->buf);
	free(fb);
}

//--------------------------------------------------------------------------
// Get a line of arbitrary length from an input stream
//--------------------------------------------------------------------------
int fgetlineFlexbuf(Flexbuf fb, FILE* in) {
	int lineLength;
	int ch;

	// Allocate initial buffer if needed
	if (fb->buf == NULL) {
		fb->len = INITIAL_CHUNK_SIZE;
		fb->buf = safe_malloc( INITIAL_CHUNK_SIZE);
	}

	// Read line
	lineLength = 0;
	do {
		// Ensure that buffer has room for at least two
		// more characters
		if (fb->len - lineLength < 2) {
			fb->len *= 2; // double its length
			fb->buf = safe_realloc(fb->buf, fb->len);
		}
		// Read and process a character
		ch = fgetc( in );
		if (ch==EOF) break;
		fb->buf[ lineLength++ ]= ch;
	} while (ch != '\n');
	fb->buf[ lineLength ] = '\0';	// add terminating null
	
	// return line length (excluding terminating null)
	return lineLength;
}

//--------------------------------------------------------------------------
// Return a read-only pointer to the string buffer
//--------------------------------------------------------------------------
const char* toStringFlexbuf(const_Flexbuf fb) {
	return fb->buf;
}

//--------------------------------------------------------------------------
// Detach string buffer from flexbuf and return
//--------------------------------------------------------------------------
char* extractFlexbuf(Flexbuf fb) {
	char* ret = fb->buf;
	fb->buf = NULL;
	fb->len = 0;
	return ret;
}

//--------------------------------------------------------------------------
// Return allocation size of flexbuf
//--------------------------------------------------------------------------
int buflenFlexbuf(const_Flexbuf fb) {
	return fb->len;
}
