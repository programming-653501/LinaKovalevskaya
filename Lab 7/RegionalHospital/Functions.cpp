
#include "Functions.h"


FILE* openStreamForReading(FILE* stream, const char* fileName)
{
	errno_t error;

	error = fopen_s(&stream, fileName, "rb");
	if (error != 0)
		printf("The file %s was not opened\n", fileName);

	return stream;
}


FILE* openStreamForWriting(FILE* stream, const char* fileName)
{
	errno_t error;

	error = fopen_s(&stream, fileName, "wb");
	if (error != 0)
		printf("The file %s was not opened\n", fileName);
	
	return stream;
}


void closeStream(FILE* stream, const char* fileName)
{
	errno_t error;
	if (stream != NULL)
	{
		error = fclose(stream);
		if (error != 0)
			printf("The file %s was not closed\n", fileName);
	}
}


void formInnerFilePath(char* filePath, const char* directoryPath, const char* fileName, const char* extension)
{
	strncpy_s(filePath, _MAX_PATH, directoryPath, _MAX_PATH);
	strcat_s(filePath, _MAX_PATH, INNER_DIRECTORY);
	strcat_s(filePath, _MAX_PATH, fileName);
	strcat_s(filePath, _MAX_PATH, extension);
}


void formSubdirectoryPath(char* subdirectoryPath, const char* directoryPath, const char* subdirectoryName)
{
	strncpy_s(subdirectoryPath, _MAX_PATH, directoryPath, _MAX_PATH);
	strcat_s(subdirectoryPath, _MAX_PATH, INNER_DIRECTORY);
	strcat_s(subdirectoryPath, _MAX_PATH, subdirectoryName);
}


bool my_fgets(char* buffer, int bufferSize)
{
	fgets(buffer, bufferSize, stdin);

	char* p = buffer;
	int counter = 0;
	while (counter <= bufferSize)
	{
		if (*p == '\n')
		{
			*p = '\0';
			return true;
		}
		p++;
		counter++;
	}
	return false;
}


void my_fflush()
{
	int ch = 0;
	while (ch != '\n')
	{
		ch = getchar();
	}
}


void enterDouble(double* num)
{
	int check = 0;

	while (!check)
	{
		check = scanf_s("%lf", num);
		if (!check)
		{
			printf("Input error. Re-enter, please.\n");
			my_fflush();
		}
		else
			break;
	}
}


void enterInt(int* num)
{
	int check = 0;

	while (!check)
	{
		check = scanf_s("%d", num);
		if (!check)
		{
			printf("Input error. Re-enter, please.\n");
			my_fflush();
		}
		else
			break;
	}
}


void enterNaturalNumber(int *num)
{
	*num = 0;
	while (*num <= 0)
	{
		enterInt(num);
		if (*num <= 0)
			printf("Only natural numbers allowed. Re-enter, please.\n");
	}
}