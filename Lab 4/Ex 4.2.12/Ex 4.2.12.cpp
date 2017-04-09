
// program prints palindromes if there are any in a text file

#include "stdafx.h"
#include <stdlib.h>
#include <clocale>
#include <string.h>
#include <conio.h>

struct Symbol
{
	unsigned char symbol;
	int position;
	int odd;
	int even;
};

bool isRussianLetter(unsigned char symbol);

void toLower(unsigned char* symbol);

int getTextFileSize(FILE* stream);

bool isLeftBorder(const Symbol* array, int index);

bool isRightBorder(const Symbol* array, int index);

bool isWordBorder(const Symbol* array, int left, int right);

void setSymbolArray(FILE* stream, Symbol* array, int size);

void findSymmetry(Symbol* array);

void findPalindromeInBetween(FILE* stream, Symbol* array, int left, int right);

void findPalindromes(FILE* stream, Symbol* array);

void printPieceOfText(FILE* stream, int leftBorder, int rightBorder);


int main()
{
	setlocale(LC_ALL, "russian");

	FILE* stream;
	errno_t error;
	char file_name[] = "default.txt";

	error = fopen_s(&stream, file_name, "r");
	if (error != 0)
	{
		printf("file wasn't opened\n");
		exit(1);
	}

	int size = getTextFileSize(stream);
	Symbol* array = new Symbol[size];

	setSymbolArray(stream, array, size);
	findSymmetry(array);
	findPalindromes(stream, array);

	delete array;

	error = fclose(stream);
	if (error != 0)
		printf("file wasn't closed\n");

	_getch();
	return 0;
}


bool isRussianLetter(unsigned char symbol)
{
	if (symbol >= 192 && symbol <= 255)
		return true;
	return false;
}


void toLower(unsigned char* symbol)
{
	if (*symbol < 224)
	{
		*symbol += 32;
	}
}


int getTextFileSize(FILE* stream)
{
	int size = 0;

	fseek(stream, 0, SEEK_END);
	size = ftell(stream) + 1;
	rewind(stream);

	return size;
}


bool isLeftBorder(const Symbol* array, int index)
{
	if (index == 0)
		return true;

	return (array[index].position - array[index - 1].position != 1);
}


bool isRightBorder(const Symbol* array, int index)
{
	if (index == 0)
		return true;

	return (array[index + 1].position - array[index].position != 1);
}


bool isWordBorder(const Symbol* array, int left, int right)
{
	return (isLeftBorder(array, left) && isRightBorder(array, right));
}


void setSymbolArray(FILE* stream, Symbol* array, int size)
{
	int ch, i = 0;
	while ((ch = fgetc(stream)) != EOF)
	{
		if (isRussianLetter(ch))
		{
			int pos = ftell(stream);
			array[i].position = pos;
			array[i].symbol = ch;
			toLower(&array[i].symbol);
			array[i].even = array[i].odd = 0;
			i++;

		}

	}
	array[i].symbol = '\0';
	array[i].position = -1;
}


void findSymmetry(Symbol* array)
{
	for (int i = 0; array[i].symbol; i++)
	{
		int k = 1;
		while ((array[i - k].symbol == array[i + k].symbol))
		{
			array[i].odd++;
			k++;
		}

		k = 0;
		while (array[i - 1 - k].symbol == array[i + k].symbol)
		{
			array[i].even++;
			k++;
		}
	}
}


void findPalindromeInBetween(FILE* stream, Symbol* array, int left, int right)
{
	while (!isWordBorder(array, left, right) && left<right)

	{
		left++;
		right--;
	}

	if (left < right)
	{

		printPieceOfText(stream, array[left].position, array[right].position);
	}
}


void findPalindromes(FILE* stream, Symbol* array)
{
	int left = 0, right = 0;
	for (int i = 0; array[i].symbol; i++)
	{
		if (array[i].odd)
		{
			left = i - array[i].odd;
			right = i + array[i].odd;
			findPalindromeInBetween(stream, array, left, right);
		}

		if (array[i].even)
		{
			left = i - array[i].even,
				right = i + array[i].even - 1;
			findPalindromeInBetween(stream, array, left, right);
		}
	}
}


void printPieceOfText(FILE* stream, int leftBorder, int rightBorder)
{
	if (stream == NULL)
		return;

	fseek(stream, leftBorder - 1, SEEK_SET);
	while (ftell(stream) < rightBorder)
		putchar(fgetc(stream));

	putchar('\n');
}
