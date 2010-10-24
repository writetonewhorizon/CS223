/*
	Created by: Douglas von Kohorn
	Course: CS223
	Term: Spring 2008
	Problem Set #4
*/

#ifndef WORDFREQ_H_
#define WORDFREQ_H_

#include "flex.h"
#include <stdio.h>

typedef struct
{
	char store[30];
	int frequency;
} wordFreq;

int fill(Flex cart, FILE* input);
void process(Flex cart);

void startGroup(wordFreq* wf, char* ctl);
void endGroup(char* ctl, wordFreq* wf);
wordFreq newWordFreq(void);

#endif
