// Douglas von Kohorn
// CPSC 223b, Spring 2008
// Problem set 8: Hamming code

#include <stdio.h>
#include "hamming.h"
#include "util.h"

#define BITSTRING unsigned int
#define N (8*sizeof(BITSTRING))

int parity(BITSTRING x);
void printbin(BITSTRING x);

unsigned int encode( unsigned int data )
{
	BITSTRING word = data;
	BITSTRING m3r,m3i,y3r,y3l,m4r,m4i,y4r,y4l,m5r,m5i,y5r,y5l;

	m5r = (1<<15)-1;
	m5i = ~m5r;
	y5r = word&m5r;
	y5l = word&m5i;
	word = (y5l<<1)|y5r;

	m4r = (1<<23)-1;
	m4i = ~m4r;
	y4r = word&m4r;
	y4l = word&m4i;
	word = (y4l<<1)|y4r;

	m3r = (1<<27)-1;
	m3i = ~m3r;
	y3r = word&m3r;
	y3l = word&m3i;
	word = (y3l<<1)|y3r;

	BITSTRING maskC1 = 357913941;
	BITSTRING maskC2 = 322122547;
	BITSTRING maskC3 = 118427407;
	BITSTRING maskC4 = 8323327;
	BITSTRING maskC5 = 32767;

	BITSTRING p1,p2,p3,p4,p5;
	p1 = parity(word&maskC1)<<30;
	p2 = parity(word&maskC2)<<29;
	p3 = parity(word&maskC3)<<27;
	p4 = parity(word&maskC4)<<23;
	p5 = parity(word&maskC5)<<15;

	word = ((((word|p1)|p2)|p3)|p4)|p5;

	return word;
}

unsigned int decode( unsigned int codeword )
{
	BITSTRING word = codeword;

	BITSTRING C1,C2,C3,C4,C5,E;
	BITSTRING maskC1 = 1431655765;
	BITSTRING maskC2 = 858993459;
	BITSTRING maskC3 = 252645135;
	BITSTRING maskC4 = 16711935;
	BITSTRING maskC5 = 65535;
	C1 = parity(codeword&maskC1);
	C2 = parity(codeword&maskC2)<<1;
	C3 = parity(codeword&maskC3)<<2;
	C4 = parity(codeword&maskC4)<<3;
	C5 = parity(codeword&maskC5)<<4;
	E=(((C1|C2)|C3)|C4)|C5;

	if(E!=0)
	{
		BITSTRING flipper = (1<<(E-1));
		word = word^flipper;
	}

	//remove parity bits
	word = (word << 3) >> 3;

	BITSTRING m3r,m3i,y3r,y3l,m4r,m4i,y4r,y4l,m5r,m5i,y5r,y5l;

	m5r = (1<<15)-1;
	m5i = ~m5r;
	y5r = word&m5r;
	y5l = word&m5i;
	if((y5l>>15) % 2 == 1) y5l = (y5l&(y5l-1));
	word = (y5l>>1)|y5r;

	m4r = (1<<22)-1;
	m4i = ~m4r;
	y4r = word&m4r;
	y4l = word&m4i;
	if((y4l>>22) % 2 == 1) y4l = (y4l&(y4l-1));
	word = (y4l>>1)|y4r;

	m3r = (1<<25)-1;
	m3i = ~m3r;
	y3r = word&m3r;
	y3l = word&m3i;
	if((y3l>>25) % 2 == 1) y3l = (y3l&(y3l-1));
	word = (y3l>>1)|y3r;

	return word;
}

int parity( BITSTRING x )
{
  int n = N;
  while (n != 1) {
    n >>= 1;
    x ^= (x >> n);
  }
  return x&1;
}

void printbin(BITSTRING x)
{
	printf("\n");
  for (int k=N-1; k>=0; k--) {
    printf( "%u", (x >> k) & 1 );
  }
	printf("\n");
}
