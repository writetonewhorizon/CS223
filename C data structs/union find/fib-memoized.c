/*
 *  fib-memoized.c
 *  fibonacci example
 *
 *  Copyright 2006, 2007 by Michael Fischer. All rights reserved.
 *
 */

#include <stdio.h>

#define EMPTY (-1)	// marks empty cache slot

// prototypes
int fib(int n);
int fibMemo(int n, int* cache);

// -------------------------------------------------------------
int main(int argc, const char * argv[]) {
	int n;
	int ch;
	printf( "Memoized recursive Fibonacci number calculator\n");
	for (;;) {
		printf("Please enter a number (-1 to quit): ");
		while (scanf("%d", &n) != 1) {
			do
				ch=getchar();
			while (ch!='\n' && ch!=EOF);
			printf("Non-numeric entry.  Please try again: ");
		}
		if (n<0) break;
		printf("fib(%d) = %d\n", n, fib(n) );
	}
	printf( "Goodbye!\n" );
}

// -------------------------------------------------------------
// Memoizing Fibonacci function.
int fib(int n) {
	// create and initialize cache
	int cache[n+1];
	for (int k=0; k<= n; k++) cache[k] = EMPTY;
	
	// compute and return Fibonacci number	
	return fibMemo(n, cache);
}

// -------------------------------------------------------------
// Recursive memoized Fibonacci function
int fibMemo(int n, int cache[]) {
	if (cache[n] != EMPTY) return cache[n];
	if (n <= 1) return 1;
	return cache[n] = fibMemo(n-1, cache) + fibMemo(n-2, cache);
}
