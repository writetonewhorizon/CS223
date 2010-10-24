/*
	Created by: Douglas von Kohorn
	Course: CS223
	Term: Spring 2008
	Problem Set #4
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "util.h"
#include "flex.h"
#include "wordfreq.h"

// -----------------------------------------------------
int fill(Flex cart, FILE* input)
{
	// put some things into the cart
	char buf[100];
	String newStr;
	int ret;

	for (;;)
	{
		ret = fscanf(input, "%99s", buf);
		printf("%s\n", buf);

		//special case: EOF or garbage characters within the file
		if(ret != 1)
		{
			if(feof(input)) return EOF;
			if(ferror(input)) fatal("Error reading stdin");
			buf[0] = '\0';
		}

		//cleans up any leading non-alphanumberic characters
		while(!isalnum(buf[0]))
		{
			//in case string is only non-alphanumeric characters or just unimportant
			if(strlen(buf) < 3) break;

			int i;
			for(i = 1; i < strlen(buf) + 1; i++) buf[i-1] = buf[i];
		}

		//cleans up any trailing non-alphanumeric characters
		while(!isalnum(buf[strlen(buf)-1]))
		{
			//in case string is only non-alphanumeric characters or just unimportant
			if(strlen(buf) < 3) break;

			buf[strlen(buf)-1] = '\0';
		}


		//special case: cleaned up word is less than 3 or greater than 30
		if(strlen(buf) < 3 || strlen(buf) > 30) continue;

		//converts all uppercase to lowercase within the string
		int i;
		for(i = 0; i < strlen(buf); i++)
		{
			if(buf[i] >= 65 && buf[i] <= 90) buf[i] += 32;
		}

		// copy contents of buf to new String
		newStr = safe_malloc(strlen( buf )+1);
		strcpy(newStr, buf);
		insertFlex(cart, newStr);
	}
	return 0;
}

// -----------------------------------------------------
void process( Flex cart )
{
	// sort cart
	sortFlex( cart );
	
	// get its length and contents
	int len = lenFlex(cart);
	String* wordList = extractFlex(cart);
	int j;
	for(j=0;j<len;j++)
	{
		printf("---%s\n",wordList[j]);
	}


	//Start control break logic (count frequency of all words)
	wordFreq current;
	char control[30];
	int i = 0;

	strcpy(current.store, wordList[i]);
	startGroup(&current, control);

	for(i = 1; i < len; i++)
	{
		if(strcmp(control, current.store) != 0)
		{
			endGroup(control, &current);
			startGroup(&current, control);
		}
		current.frequency += 1;
		strcpy(current.store, wordList[i]);
	}

	endGroup(control, &current);
	//End control break logic

	//FREEEEEEEDOOOOOOM
	int k;
	for (k=0; k<len; k++)
	{
		free(wordList[k]);
	}

	free(wordList);
}

// ---------------------------------------------------------------------
// Process start of group
void startGroup(wordFreq* wf, char* ctl)
{
	// print group heading here, if desired
	strcpy(ctl, wf->store);
	wf->frequency = 0;
}

// ---------------------------------------------------------------------
// Process end of group
void endGroup(char* ctl, wordFreq* wf)
{
	printf("%30s.....%i\n", ctl, wf->frequency );
}
