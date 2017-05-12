#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Constants.h"


FILE* openStreamForReading(FILE* stream, const char* fileName);

FILE* openStreamForWriting(FILE* stream, const char* fileName);

void closeStream(FILE* stream, const char* fileName);

void formInnerFilePath(char* filePath, const char* directoryPath, const char* fileName, const char* extension = TXT);

void formSubdirectoryPath(char* subdirectoryPath, const char* directoryPath, const char* subdirectoryName);

bool my_fgets(char* buffer, int bufferSize);

void my_fflush();

void enterDouble(double* num);

void enterInt(int* num);

void enterNaturalNumber(int *num);

