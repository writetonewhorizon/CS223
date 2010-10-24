/*created by: Douglas von Kohorn
PS9
*/
// Michael J. Fischer
// CPSC 223b, Spring 2008
// Problem set 9: Huffman code

/*
 *  ibitstream.c
 *
 *  Created by Michael Fischer on 2/16/06.
 *  fischer-michael@cs.yale.edu
 *  For use in Yale course CPSC 223b, Spring 2006
 *
 *  Copyright (C) 2006 by Michael Fischer. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "util.h"

#include "bitstring.h"
#include "ibitstream.h"

// Define opaque type
struct ibitstream {
	FILE* fp;
	int cursize; /* #bytes in buf */
	int buf[3];  /* byte buffer */
	int numbits; /* #bits left in buf[0] */
	int shift;   /* shift amount to get next bit */
};

// ------------------------------------------------------------------
// Open an input bit stream on top of an already-open byte stream
Ibitstream openIbitstream(FILE* in) {
	Ibitstream ibs = safe_malloc( sizeof *ibs);
	ibs->fp = in;

	/* fill the buffer */
	for (ibs->cursize = 0; ibs->cursize<3; ibs->cursize++) {
		int ch= getc( ibs->fp );
		if ((ibs->buf[ ibs->cursize ] = ch) == EOF)
			break;
	}

	/* empty file is not a valid file encoding */
	if (ibs->cursize == 0)
		fatal("Invalid empty encoded file\n");

	/* initialize remaining bit count and shift amounts */
	ibs->numbits = 8;
	ibs->shift = 7;
	if (ibs->cursize == 1)
		ibs->numbits = 0; /* special case for empty bit stream */
	if (ibs->cursize == 2)
		ibs->numbits -= ibs->buf[1];
	return ibs;
}

// ------------------------------------------------------------------
// Close the bit stream and free the Ibitstream data structure
void closeIbitstream(Ibitstream ibs) {
	free(ibs);
}

// ------------------------------------------------------------------
// Read and return the next bit from the Ibitstream.
// Returns EOF if no unread bits remain.
int getIbitstream(Ibitstream ibs) {
	if (ibs->numbits <= 0) {
		/* buf[0] is empty, so try to refill */
		if (ibs->cursize < 3)
			return EOF; /* no more bytes in byte stream */
		ibs->numbits = 8;
		ibs->shift = 7;
		ibs->buf[0] = ibs->buf[1];
		ibs->buf[1] = ibs->buf[2];
		ibs->buf[2] = getc( ibs->fp );
		if (ibs->buf[2] == EOF) {
			ibs->cursize--;
			ibs->numbits -= ibs->buf[1];
		}
	}

	/* pick up bit number k from buf[0], where k = ibs->numbits-1 */
	ibs->numbits--;
	return (ibs->buf[0] >> ibs->shift--) & 1;
}
