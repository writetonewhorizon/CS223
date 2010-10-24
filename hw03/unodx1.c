#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "util.h"

#define MAXLENGTH 99

int main()
{
	int readLine(char[], int);
	int linenumber;

	for(linenumber = 0;;linenumber++)
	{
		char buf[MAXLENGTH+1];
		if(readLine(buf,linenumber) == EOF) break;
	}

	return 0;
}

int readLine(char buf[], int linenumber)
{
	int pos, realpos,  bytenumber, ch, ret;
	unsigned char letter;

	ret = scanf("%99[^\n]", buf);
	if(ret != 1)
	{
		if(feof(stdin)) return EOF;
		if(ferror(stdin)) fatal("Error reading stdin");
		buf[0] = '\0';
	}

	ch = getchar();

	if(ch == EOF) fatal("No newline at the end of file");
	if(ch != '\n') fatal("Line exceeds maximum length");

	int i;
	for(i = 0; i < strlen(buf); i++)
	{
		if((buf[i] > 32 && buf[i] < 43) || (buf[i] > 43 && buf[i] < 48) || (buf[i] > 57 && buf[i] < 65) || (buf[i] > 71 && buf[i] < 97) || buf[i] > 102)
		{
			//checks for possible garbage characters
			fatal("Invalid characters, line number: %i", linenumber);
		}
	}


	ret = sscanf(buf, "%d%n", &bytenumber, &pos);
	if(ret != 1 || bytenumber < 0 || bytenumber > INT_MAX || bytenumber < (linenumber-1)*16 || bytenumber > linenumber*16)
	{
		//makes sure valid byte positions
		fatal("Invalid byte position or previous line, line number: %i", linenumber);
	}

	realpos = pos;
	int numRead;
	for(numRead = 0; realpos < strlen(buf); realpos+=pos, numRead++)
	{
		ret = sscanf(buf+realpos, "%hhx%n", &letter, &pos);
		//checks for too many numbers, but accounts for possible trailing whitespace
		if(numRead > 15 && ret == 1) fatal("Too many numbers on one line, line number: %i", linenumber);
		printf("%c",letter);
	}

	return 0;
}
