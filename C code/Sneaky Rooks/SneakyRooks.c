// Christian Lozano COP 3502C NID:4233003
// Program assignment 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SneakyRooks.h"
#define BASE 26
#define INTIAL 1



// Functional Prototypes
// fix the multiple digit problem
// frees all memory that was allocated for
void destroyboard(Coordinate *temp, int *parttwo, int *partone)
{
	free(temp);
	free(partone);
	free(parttwo);

}

// checks if all the given rook locations are safe from eachother
int allTheRooksAreSafe(char **rookStrings, int numRooks, int boardSize)
{
	int i, j;
	
	int *whichCol = calloc(boardSize + INTIAL, sizeof(int));
	int *checkRow = calloc(boardSize + INTIAL, sizeof(int));	
	
	Coordinate *temp = malloc(sizeof(Coordinate));

	// for loop that goes through all the rooks
	for (i = 0; i < numRooks; i++)
	{
		//make corrdinates be placed into a temp struct
		parseCoordinateString(rookStrings[i], temp);

		// checks to see if there is already a value in the column i need to put it in
		// using the index as column and the number inside as the row 
		// returns zero if there is something in there already
		if (whichCol[temp->col] != 0)
		{
			destroyboard(temp, whichCol, checkRow);

			return 0;
		}

		// otherwise it assigns that column with its row
		else
		{
			whichCol[temp->col] = temp->row;
		}
	}
	// for loop checks for the board side and sees if there are any numbers that are repeating in the array I made above
	// since if it is repeating it means they got assigned diffrent letters but the same row wiich is not safe
	for (j = INTIAL; j <= boardSize; j++)
	{

		// checks to see if there is a repeat
		if (checkRow[whichCol[j]] == INTIAL && whichCol[j] != 0)
		{
			destroyboard(temp, whichCol, checkRow);

			return 0;
		}
		//if it's not a repeat then place a marker to say this is occupied
		else
		{
			checkRow[whichCol[j]] = INTIAL;
		}
	}

	destroyboard(temp, whichCol, checkRow);

	return 1;
}

// function that takes a to the power of b
int powerof(int a, int b)
{
	int i, result = INTIAL;

	for(i = 0; i < b; i++)
	{
		result *= a;
	}

	// returns outcome
	return result;
}

// turns string into corrdinates and puts it in struct
void parseCoordinateString(char *rookString, Coordinate *rookCoordinate)
{
	int i = 0, j = 0 , l = 0, k, value = 0;
	// making array to store the row and column coordinates
	char row[strlen(rookString)], col[strlen(rookString)];

	// checking how many letters
	while(rookString[i] <= 'z' && rookString[i] > '9')
	{
		col[l++] = rookString[i++];
	}

	// using base converstion to make it into an integer
	for (k = i-INTIAL; k >= 0; k--)
	{	
		value += (col[k]-'a'+ INTIAL) * powerof(BASE, i - k - INTIAL);
		
	}

	// the remaining will be numbers and use atoi to mkae the string of numbers into a int
	while(rookString[i] <= '9')
	{
		row[j++] = rookString[i++];
	}

	// putting the data into the stuct
	rookCoordinate -> col = value;
	rookCoordinate -> row = atoi(row);
}

// rating of diffculty
double difficultyRating(void)
{
	return 2;
}

// hours spent working on this assignment
double hoursSpent(void)
{
	return 10;
}