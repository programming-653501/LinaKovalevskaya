#pragma once

#include "FullName.h"
#include "Constants.h"


class MedicalWorker
{
private:

	int hospitalUnitNo_;
	int medicalWorkerNo_;

	int currentPatientsAmount_;

	FullName fullName_;

	char post_[MAX_POST_LENGTH];
	char speciality_[MAX_SPECIALITY_LENGTH];

	MedicalWorker() : currentPatientsAmount_(0) {}
	MedicalWorker(int medicalWorkerNo) : medicalWorkerNo_(medicalWorkerNo) {}

	MedicalWorker(int hospitalUnitId, int id, 
				  const char* name, const char* surname, 
				  const char* post, const char* speciality);

	MedicalWorker(const char* name, const char* surname,
		const char* post, const char* speciality);

	void setWorkingPosition(const char* post, const char* speciality);
	void setFullName(const char* name, const char* surname);

	void increaseCurrentPatientsAmount();
	void decreaseCurrentPatientsAmount();

	void printInformation();

	friend class HospitalUnit;
};


