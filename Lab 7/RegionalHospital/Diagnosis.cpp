#include "Diagnosis.h"

Diagnosis::Diagnosis(const char* diagnosis, int hospitalUnitNo, int key)
{
	hospitalUnitNo_ = hospitalUnitNo;
	key_ = key;
	strncpy_s(diagnosis_, diagnosis, MAX_DIAGNOSIS_LENGTH - 1);
}