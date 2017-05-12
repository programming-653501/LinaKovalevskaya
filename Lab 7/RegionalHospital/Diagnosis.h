#pragma once

#include <string.h>

#include "Constants.h"


class Diagnosis
{
public:

	char diagnosis_[MAX_DIAGNOSIS_LENGTH];
	
	int hospitalUnitNo_;
	int key_;
	
	Diagnosis(const char* diagnosis, int hospitalUnitNo, int key);
	Diagnosis() {}
};


class DiagnosisListItem
{
public:

	DiagnosisListItem* next;
	Diagnosis diagnosis;
};