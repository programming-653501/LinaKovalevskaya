
#include "MedicalWorker.h"


void MedicalWorker::setWorkingPosition(const char* post, const char* speciality)
{
	strncpy_s(post_, post, MAX_POST_LENGTH - 1);
	strncpy_s(speciality_, speciality, MAX_SPECIALITY_LENGTH - 1);
}


MedicalWorker::MedicalWorker(int hospitalUnitNo, int medicalWorkerNo,
							 const char* name, const char* surname,
							 const char* post, const char* speciality)
{
	hospitalUnitNo_ = hospitalUnitNo;
	medicalWorkerNo_ = medicalWorkerNo;
	setFullName(name, surname);
	setWorkingPosition(post, speciality);
	currentPatientsAmount_ = 0;
}


void MedicalWorker::setFullName(const char* name, const char* surname)
{
	fullName_ = FullName(name, surname);
}


MedicalWorker::MedicalWorker(const char* name, const char* surname,
	const char* post, const char* speciality)
{
	setFullName(name, surname);
	setWorkingPosition(post, speciality);
	currentPatientsAmount_ = 0;
}


void MedicalWorker::increaseCurrentPatientsAmount()
{
	currentPatientsAmount_++;
}

void MedicalWorker::decreaseCurrentPatientsAmount()
{
	currentPatientsAmount_ > 0 ? (currentPatientsAmount_--) : (currentPatientsAmount_ = 0);
}

void MedicalWorker::printInformation()
{
	printf("\nH.U.%d No%d\t", hospitalUnitNo_, medicalWorkerNo_);
	fullName_.print();
	printf("\nPost: %s\tSpeciality: %s\t", post_, speciality_);
	printf("Current amount of patients: %d\n", currentPatientsAmount_);
}