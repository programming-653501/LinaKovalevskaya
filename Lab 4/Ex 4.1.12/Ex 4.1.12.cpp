
// program creates a frequency dictionary for a text stream 

#include "stdafx.h"
#include <conio.h>
#include "FrequencyDictionary.h"


#define TYPE_TEXT '1'
#define DEFAULT_TEXT '2'


int main()
{
	char defaultStream[] = "default.txt";
	FrequencyDictionary dictionary(defaultStream);

	char choice;
	printf("Press 1 - to type text yourself\n      2 - to use default file\t");
	scanf_s("%c", &choice);

	if (choice == TYPE_TEXT)
	{
		printf("Type your text\n(press Enter, then Ctrl+Z to stop input).\n\n");
		dictionary.addWordFromStdin();
	}

	else if (choice == DEFAULT_TEXT)
	{
		dictionary.printDefaultText();
		dictionary.addWordFromDefaultStream();
	}

	else
	{
		printf("Bad choice\n");
		_getch();
		return 0;
	}

	dictionary.sort();
	dictionary.show();
	
	_getch();
	return 0;
}

