
#include "FullName.h"


FullName::FullName()
{
	strncpy_s(name_, DEFAULT_NAME, MAX_WORD_LENGTH - 1);
	strncpy_s(surname_, DEFAULT_NAME, MAX_WORD_LENGTH - 1);
}


FullName::FullName(const char* name, const char* surname)
{
	strncpy_s(name_, name, MAX_WORD_LENGTH - 1);
	strncpy_s(surname_, surname, MAX_WORD_LENGTH - 1);
}


void FullName::enterName()
{
	printf("Name: ");
	if (!my_fgets(name_, MAX_WORD_LENGTH))
		my_fflush();
}


void FullName::enterSurname()
{
	printf("Surname: ");
	if(!my_fgets(surname_, MAX_WORD_LENGTH))
		my_fflush();
}


void FullName::enterFullName()
{
	enterName();
	enterSurname();
}


void FullName::print()
{
	printf("%s %s", name_, surname_);
}