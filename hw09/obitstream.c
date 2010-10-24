/*created by: Douglas von Kohorn
PS9
*/
// Michael J. Fischer
// CPSC 223b, Spring 2008
// Problem set 9: Huffman code

/*
 *  obitstream.c
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
#include "obitstream.h"

// Define opaque type
struct obitstream {
	FILE* fp;
	int buf; /* byte buffer, right justified */
	int numbits; /* #bits in buf */
};

// ------------------------------------------------------------------
// Open an output bit stream on top of an already-open byte stream
Obitstream openObitstream(FILE* out) {
	Obitstream obs = safe_malloc( sizeof *obs);
	obs->fp = out;
	obs->buf = 0;
	obs->numbits = 0;
	return obs;
}

// ------------------------------------------------------------------
// Close the bit stream, flushing to the underlying byte stream any
// unwritten bits along with padding information; then free the
// Obitstream data structure.
void closeObitstream(Obitstream obs) {
	if (obs->fp != NULL) {
		/* pad last byte and write out filler length byte */
		int numfiller; // # filler bits
		if (obs->numbits > 0) { // fill partial byte
			numfiller = 8 - obs->numbits;
			obs->buf <<= numfiller;
			putc( obs->buf, obs->fp );
			// write partial data byte
		} else { // last byte written was full
			numfiller = 0; // so no filler needed
		}
		// write # filler bits
		putc( numfiller, obs->fp );
	}
	free(obs);
}

// ------------------------------------------------------------------
// Write 'bit' to the Obitstream, buffering as necessary.
void putbObitstream(Obitstream obs, int bit) {
	/* put bit in buffer */
	obs->buf = (obs->buf << 1) | bit;
	obs->numbits++;

	/* if buffer is full, write it out */
	if (obs->numbits == 8) {
		putc( obs->buf, obs->fp );
		obs->numbits = 0;
	}
}

// ------------------------------------------------------------------
// Write all of the bits in Bitstring 'bs' to the Obitstream.
void putsObitstream(Obitstream obs, Bitstring bs) {
	BitstringIter bsi = newBitstringIter(bs);
	while (hasNextBitstringIter(bsi)) {
		putbObitstream(obs, nextBitstringIter(bsi));
	}
	freeBitstringIter(bsi);
}
