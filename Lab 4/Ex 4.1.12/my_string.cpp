
#include "my_string.h"

int my_strlen(const char* str)
{
	int length = 0;
	while (*str)
	{
		length++;
		str++;
	}

	return length;
}


void my_strcpy(char* destination, const char* source)
{
	int i = 0, source_length = my_strlen(source);
	while (i <= source_length)
	{
		destination[i] = source[i];
		i++;
	}
}


int my_strcmp(const char* str1, const char* str2)
{
	while (*str1 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return ((*str1 > *str2) - (*str1 < *str2));
}


void toLower(char* ch)
{
	if (*ch >= 'A' && *ch <= 'Z')
		*ch += 'a' - 'A';
}


void toLowerCase(char* str)
{
	while (*str)
	{
		toLower(str);
		str++;
	}
}


bool isLetter(char symbol)
{
	if ((symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z'))
		return true;

	return false;
}

bool isSingleQuote(char symbol)
{
	if (symbol == '\'')
		return true;

	return false;
}