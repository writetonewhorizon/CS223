// Example of opening and reading a file

#include <stdio.h>

int main(int argc, char* argv[]) {

	// check for exactly one command line argument
	if (argc != 2) {
		printf("usage: %s filename\n", argv[0]);
		return 1; // wrong number of args
	}

	// get file name from command line argument vector
	char* infile = argv[1];

	// try to open the file
	printf("Attempting to open file %s for reading\n", infile);
	FILE* in; // defines in to be a stream
	in = fopen(infile, "r");
	if (in == NULL) {
		printf("Failed to open file %s for reading\n", infile);
		return 2; // can't open file
	}

	// copy file to stdout
	printf("File %s successfully opened for reading\n", infile);
	printf("\nContents of file %s:\n"
		"------------------------------\n", infile);
	// copy file to stdout
	int ch;
	for (;;) {
		ch = getc( in ); // read character from stream in
		if (ch == EOF) break;
		putchar(ch);
	}

	// exit
	printf("------------------------------\n"
		"EOF reached.  Goodbye.  \n");
}

