#pragma once

#include "Functions.h"


class FullName
{
public:
	
	FullName();
	FullName(const char* name, const char* surname);

	void enterFullName();
	void enterName();
	void enterSurname();

	void print();

private:

	char name_[MAX_WORD_LENGTH];
	char surname_[MAX_WORD_LENGTH];
};

