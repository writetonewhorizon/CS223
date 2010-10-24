/*
	Created by: Douglas von Kohorn
	Course: CS223
	Term: Spring 2008
	Problem Set #2
*/
#include <stdio.h>
#include <math.h>
#include <limits.h>
#define PI (2*acos(0.0))

int main()
{
	int numGuests, circleLayer, squareLayer, circlePortions, squarePortions;
	double usedSquareArea, usedCircleArea, servingSize;
	double totalSquareArea, totalCircleArea;

	for(;;)
	{
		printf("How many guests are you planning on serving? ");
		if(scanf("%i",&numGuests) == 1 && numGuests > 0 && numGuests < INT_MAX) break;
		else puts("Invalid input, please try again.");
		while ( getchar() != '\n' );
	}

	for(;;)
	{
		printf("What is your desired serving size? ");
		if(scanf("%lg", &servingSize) == 1 && servingSize >= 1.0 && servingSize <= 8.0) break;
		else puts("Invalid input, please try again.");
		while ( getchar() != '\n' );
	}

	int i,tempPortions;
	double tempArea;

	totalSquareArea = 0;
	totalCircleArea = 0;
	usedCircleArea = 0;
	usedSquareArea = 0;

	for(i = 0, tempPortions = 0, tempArea = 0, circlePortions = 0; servingSize * numGuests > usedCircleArea; i++)
	{
		tempArea = ((2*i+6)*(2*i+6)*PI)*.25;
		tempPortions = floor(tempArea/servingSize);

		totalCircleArea += tempArea;
		usedCircleArea += tempPortions * servingSize;
		circlePortions += tempPortions;

		tempPortions = 0;
		tempArea = 0;
	}

	circleLayer = i-1;

	for (i = 0, tempPortions = 0, tempArea = 0, squarePortions = 0; servingSize * numGuests > usedSquareArea; i++)
	{
		tempArea = ((2*i+6)*(2*i+6));
		tempPortions = floor(tempArea/servingSize);
		
		totalSquareArea += tempArea;
		usedSquareArea += tempPortions * servingSize;
		squarePortions += tempPortions;

		tempPortions = 0;
		tempArea = 0;
	}

	squareLayer = i-1;

	printf("A round cake of size %i for serving %i guests will yield %i portions. It will cost $%g.00.\n", circleLayer*2 + 6, numGuests, circlePortions, round(2*(circleLayer+1) + .5*totalCircleArea));
	printf("A square cake of size %i for serving %i guests will yield %i portions. It will cost $%g.00.\n", squareLayer*2 + 6, numGuests, squarePortions, round(2*(squareLayer+1) + .55*totalSquareArea));

	return 0;
}
