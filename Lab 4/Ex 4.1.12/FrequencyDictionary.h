#pragma once

#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 80


struct Word
{
	char* word;
	int counter;
};

class FrequencyDictionary
{
private:

	int counter_,
		available_;
	Word* array_;
	FILE* defaultStream_;
	char* defaultName_;

	void increazeSize(void);
	void openDefaultStream(void);
	int getWordFromStream(FILE* stream, char* word);
	void addWordFromStream(FILE* stream);
	void addWord(char* word);
	int doesWordAlreadyExist(const char* word);
	void quickSort(int left, int right);

public:

	FrequencyDictionary(const char* defaultName);

	void addWordFromDefaultStream(void);
	void addWordFromStdin(void);
	void printDefaultText(void);
	void sort(void);
	void show(void);

	~FrequencyDictionary(void);
};
