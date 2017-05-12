#pragma once

#include "HospitalUnit.h"
#include "RunMode.h"


class Hospital
{
public:

	Hospital();
	~Hospital();

	void createDefaultHospital();

	void restoreHospitalFromFile();
	void writeHospitalToFile();

	void workWith();

private:

	char name_[MAX_HOSPITAL_NAME_LENGTH];
	int hospitalNo_;
	Hospital(const char* name, int hospitalNo);

	int unitsAmount_;
	int availableUnitsAmount_;
	HospitalUnit* units_;

	void addUnit(const char* unitName, int unitCapacity);
	void increaseAvailableUnitsAmount();
	void initializeUnitsArray();

	int capacity_;
	int currentPatientsAmount_;

	int currentMedicalWorkersAmount_;

	void computeCapacity();
	void computeCurrentPatientsAmount();
	void computeMedicalWorkersAmount();

	char hospitalDirectoryPath_[_MAX_PATH];
	void createHospitalDirectory();
	void createHospitalDirectoryPath(const char* currentDirectory);

	void formInnerFilesNames();
	void formDataFileName();
	void formUnitDirectoriesFileName();

	char externalDataFilePath_[_MAX_PATH];
	void writeDataToExternalFile();
	void readDataFromExternalFile();

	char dataFilePath_[_MAX_PATH];
	void writeDataToFile();
	void readDataFromFile();

	char unitDirectoriesFilePath_[_MAX_PATH];
	void writeUnitDirectoriesToFile();
	void readUnitDirectoriesFromFile();

	void chooseRandomDiagnosis(int& unitNo, int& diagnosisKey);
	void admitPatientToUnit(int unitNo, int diagnosisKey);
	void admitPatient();
	void blowOffPatient(int unitNo);
	void referPatientToUnit(int unitNo, ReceptionPatientForm receptionPatientForm, int diagnosisKey);
	void signUpPatientAtReception(ReceptionPatientForm& receptionPatientForm);

	float getAverageWorkloadPerMedicalWorker();
	float getUnitAverageWorkloadPerMedicalWorker(int unitNo);
	bool isUnitNoValid(int unitNo);
	char* getUnitName(int unitNo);
	bool isUnitFull(int unitNo);
	const char* getDiagnosisFromDatabase(int unitNo, int diagnosisKey);

	void printInformation();
	void prepareAccount();

	void printInvitation();
	void chooseUnit();
};

