
#include "stdafx.h"
#include <conio.h>
#include <ctime>
#include <iomanip>
#include <malloc.h>


int SkipUnwanted(void);
void EnterInt(int* number);
void EnterNaturalNumber(int *number);

int CheckArrayIndex(int index, int dimension);
void SwapColumns(int** array, int rows, int columns, int column1, int column2);
void SwapRows(int** array, int rows, int columns, int row1, int row2);

void ShuffleColumns(int** array, int rows, int columns);
void ShuffleRows(int** array, int rows, int columns);

int** CreateArray(int** array, int rows, int columns);
void ShowArray(int** array, int rows, int columns);

void FillFromOneToDim(int *array, int dimension, int start_num); /* fills the array with consistent numbers from 1 to the dimension
								of the array beginning from start_num */
void GenerateStandardLatinSquare(int **array, int rows, int columns); 
void GenerateLatinSquare(int** array, int rows, int columns); /* generates random latin square */


int main()
{
	int size, **square=NULL;

	printf("Enter size:\t");
	EnterNaturalNumber(&size);

	square = CreateArray(square, size, size);
	GenerateLatinSquare(square, size, size);
	ShowArray(square, size, size);

	_getch();
    return 0;
}


int SkipUnwanted(void)
{
	int ch, counter = 0;

	while ((ch = getchar()) != '\n')
		counter++;

	return counter;
}

void EnterInt(int* number)
{
	int check = 0;

	while (!check)
	{
		check = scanf_s("%d", number);
		if (!check)
		{
			printf("Only integer numbers allowed. Re-enter, please.\n");
			SkipUnwanted();
		}
		else
			break;
	}
}

void EnterNaturalNumber(int *number)
{
	*number = 0;
	while (*number <= 0)
	{
		EnterInt(number);
		if (*number <= 0)
			printf("Only natural numbers allowed. Re-enter, please.\n");
	}
}

int CheckArrayIndex(int index, int dimension)
{
	if (index >= 0 && index < dimension)
		return 1;
	return 0;
}

void SwapColumns(int** array, int rows, int columns, int column1, int column2)
{
	if (!CheckArrayIndex(column1, columns) || !CheckArrayIndex(column2, columns))
		return;

	for (int i = 0; i < rows; i++)
	{
		int temp = array[i][column1];
		array[i][column1] = array[i][column2];
		array[i][column2] = temp;
	}
}

void SwapRows(int** array, int rows, int columns, int row1, int row2)
{
	if (!CheckArrayIndex(row1, rows) || !CheckArrayIndex(row2, rows))
		return;

	for (int i = 0; i < columns; i++)
	{
		int temp = array[row1][i];
		array[row1][i] = array[row2][i];
		array[row2][i] = temp;
	}
}

void ShuffleColumns(int** array, int rows, int columns)
{
	for (int i = columns - 1; i >= 1; i--)
	{
		int j = rand() % i + 0;
		SwapColumns(array, rows, columns, i, j);
	}
}

void ShuffleRows(int** array, int rows, int columns)
{
	for (int i = rows - 1; i >= 1; i--)
	{
		int j = rand() % i + 0;
		SwapRows(array, rows, columns, i, j);
	}
}

int** CreateArray(int** array, int rows, int columns)
{
	if (!array)
	{
		array = (int**)malloc(rows * sizeof(int));
		for (int i = 0; i < rows; i++)
		{
			array[i] = (int*)malloc(columns * sizeof(int));
		}
	}

	return array;
}

void ShowArray(int** array, int rows, int columns)
{
	printf("\n");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
			printf("%d\t", array[i][j]);
		printf("\n");
	}
	printf("\n");
}

void FillFromOneToDim(int *array, int dimension, int start_num)
{
	if (!array)
		return;

	int min_value = 1, max_value = dimension;

	for (int i = 0; i < dimension; i++) {
		array[i] = start_num++;
		if (start_num > max_value)
			start_num = min_value;
	}
}

void GenerateStandardLatinSquare(int **array, int rows, int columns)
{
	if (!array || rows != columns)
		return;

	for (int i = 0; i < rows; i++)
	{
		FillFromOneToDim(array[i], columns, i + 1);
	}
}

void GenerateLatinSquare(int** array, int rows, int columns)
{
	GenerateStandardLatinSquare(array, rows, columns);
	ShuffleRows(array, rows, columns);
	ShuffleColumns(array, rows, columns);
}



