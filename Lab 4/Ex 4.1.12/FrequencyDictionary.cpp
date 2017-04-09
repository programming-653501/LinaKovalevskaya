
#include "FrequencyDictionary.h"


void FrequencyDictionary::openDefaultStream(void)
{
	errno_t error;

	error = fopen_s(&defaultStream_, defaultName_, "r");
	if (error != 0)
	{
		printf("Can not open default file\n");
		exit(1);
	}
}


FrequencyDictionary::FrequencyDictionary(const char* defaultName)
{
	available_ = 100;
	array_ = new Word[available_];
	counter_ = 0;
	defaultName_ = new char[my_strlen(defaultName) + 1];
	my_strcpy(defaultName_, defaultName);
	openDefaultStream();
}


void FrequencyDictionary::increazeSize(void)
{
	Word* buffer = new Word[2 * available_];

	for (int i = 0; i < counter_; i++)
	{
		buffer[i] = array_[i];
	}

	delete[] array_;
	array_ = buffer;
	available_ *= 2;
}


int FrequencyDictionary::getWordFromStream(FILE* stream, char* word)
{
	int current = 0, i = 0;
	char buffer[81];

	while (!isLetter(current) && !isSingleQuote(current))
		if ((current = fgetc(stream)) == EOF)
			return 0;

	while ((isLetter(current) || isSingleQuote(current)) && i < MAX_LENGTH)
	{
		buffer[i++] = current;
		current = fgetc(stream);
	}

	buffer[i] = '\0';
	my_strcpy(word, buffer);

	if (current == EOF)
		return 0;

	return 1;
}


int FrequencyDictionary::doesWordAlreadyExist(const char* word)
{
	for (int i = 0; i < counter_; i++)
		if (!my_strcmp(array_[i].word, word))
			return i;

	return -1;
}


void FrequencyDictionary::addWord(char* word)
{
	toLowerCase(word);
	int check = doesWordAlreadyExist(word);
	if (check >= 0)
	{
		array_[check].counter++;
		return;
	}

	if (counter_ >= available_)
		increazeSize();

	array_[counter_].word = new char[my_strlen(word) + 1];
	my_strcpy(array_[counter_].word, word);
	array_[counter_].counter = 1;
	counter_++;
}


void FrequencyDictionary::addWordFromStream(FILE* stream)
{
	char buffer[81];

	while (getWordFromStream(stream, buffer))
		addWord(buffer);
}


void FrequencyDictionary::quickSort(int left, int right)
{
	int i = left, j = right;
	char mid[128];
	my_strcpy(mid, array_[(left + right) / 2].word);
	do
	{
		while (my_strcmp(array_[i].word, mid) < 0)
			i++;
		while (my_strcmp(array_[j].word, mid) > 0)
			j--;

		if (i <= j)
		{
			Word temp = array_[i];
			array_[i] = array_[j];
			array_[j] = temp;
			i++;
			j--;
		}
	} while (i < j);
	if (left < j)
		quickSort(left, j);
	if (i < right)
		quickSort(i, right);

}


void FrequencyDictionary::addWordFromDefaultStream(void)
{
	addWordFromStream(defaultStream_);
}


void FrequencyDictionary::addWordFromStdin(void)
{
	addWordFromStream(stdin);
}


void FrequencyDictionary::printDefaultText(void)
{
	char* buffer = new char[256];

	while (buffer != NULL)
	{
		buffer = fgets(buffer, 256, defaultStream_);
		printf("%s", buffer);
	}

	rewind(defaultStream_);
	delete buffer;
}


void FrequencyDictionary::sort(void)
{
	quickSort(0, counter_ - 1);
}


void FrequencyDictionary::show(void)
{
	printf("\nFrequency:\n");
	for (int i = 0; i < counter_; i++)
		printf("%s\t%d\n", array_[i].word, array_[i].counter);
}


FrequencyDictionary::~FrequencyDictionary(void)
{
	for (int i = 0; i < counter_; i++)
		delete[] array_[i].word;

	delete[] array_;

	fclose(defaultStream_);

	delete defaultName_;
}