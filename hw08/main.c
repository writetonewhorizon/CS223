// Douglas von Kohorn
// CPSC 223b, Spring 2008
// Problem set 8: Hamming code

#include <stdio.h>
#include "util.h"
#include "hamming.h"

#define BITSTRING unsigned int

int getInput(FILE* in);
int executeGame(FILE* in);

int main(int argc, char* argv[])
{
	// check for exactly one command line argument
	if (argc != 2)
	{
		fatal("TOO MANY ARGUMENTS\n", argv[0]);
	}

	char* infile = argv[1];

	// try to open the file
	printf("Starting hex player on input file \"%s\"\n", infile);
	FILE* in; // defines in to be a stream
	in = fopen(infile, "r");
	if (in == NULL)
	{
		fatal("Failed to open file %s for reading\n", infile);
	}

	while(executeGame(in) != EOF) continue;

	fclose(in);

	return 0;
}

int executeGame(FILE* in)
{
	int ret;
	BITSTRING data, codeword;

	ret = fscanf( in, " 0x%x (%*[^)]) 0x%x (%*[^)])", &data, &codeword );

	if(ret != 2)
	{
		if(feof(in)) return EOF;
		if(ferror(in)) fatal("Error reading file\n");
	}

	printf("data, codeword: %d | %d \n",data,codeword);

	BITSTRING result = encode(data);
	printf("RESULT: %d\n",result);

	result = decode(codeword);
	printf("RESULT: %d\n",result);

	return 0;
}
