#pragma once

#include <direct.h>

#include "MedicalWorker.h"
#include "PatientsListItem.h"
#include "Functions.h"


class HospitalUnit
{
private:

	HospitalUnit();
	HospitalUnit(int i) : unitNo_(i) {}
	HospitalUnit(const char* name, int unitNo, int capacity);
	~HospitalUnit();

	char unitDirectoryPath_[_MAX_PATH];
	void formUnitDirectoryPath(const char* hospitalDirectory);
	void createUnitDirectory(const char* hospitalDirectory);

	char dataFilePath_[_MAX_PATH];
	void formDataFilePath();
	void writeToDataFile();
	void readFromDataFile();

	char medicalWorkersFilePath_[_MAX_PATH];
	void formMedicalWorkersFilePath();
	void writeMedicalWorkersToFile();
	void readMedicalWorkersFromFile();

	char diagnosisDatabaseFilePath_[_MAX_PATH];	
	void formDiagnosisDatabaseFilePath();
	void writeDiagnosisDatabaseToFile();
	void readDiagnosisDatabaseFromFile();

	char patientsListFilePath_[_MAX_PATH];
	void formPatientsListFilePath();
	void readPatientsListFromFile();
	void readPatientsListFromFile(FILE* stream);
	void writePatientsListToFile();	
	void writePatientsListToFile(FILE* stream);

	void formInnerFilesPath();
	
	char name_[MAX_HOSPITAL_UNIT_NAME_LENGTH];
	int unitNo_;
	int capacity_;

	int currentMedicalWorkersAmount_;
	int availableMedicalWorkersAmount_;
	MedicalWorker* medicalWorkers_;
	void initializeMedicalWorkersArray();
	
	void addMedicalWorker(MedicalWorker* medicalWorker);
	void addMedicalWorker(const char* name, const char* surname,
		const char* post, const char* speciality);
	void increaseMedicalWorkersAvailableAmount();
	void printMedicalWorkers();
	void printMedicalWorker(int medicalWorkerNo);
	
	MedicalWorker* findFreeMedicalWorkerSomehow();
	void addPatientToMedicalWorker(int medicalWorkerNo);
	void removePatientFromMedicalWorker(int medicalWorkerNo);

	int currentDiagnosisDatabaseSize_;
	int availableDiagnosisDatabaseSize_;
	Diagnosis* diagnosisDatabase_;
	void initializeDiagnosisDatabase();

	void increaseDiagnosisDatabaseSize();
	void addDiagnosisToDatabase(const char* diagnosis);
	void printDiagnosisDatabase();

	int currentPatientsAmount_;
	PatientsListItem* patientsList_;
	PatientsListItem* patientsListTail_;
	void initializePatientsList();

	void addPatientToList(Patient* patient);
	void addPatientToList(ReceptionPatientForm& receptionPatientForm, int diagnosisKey);
	void removePatientsList();
	void removePatientFromList(PatientsListItem* patientsListItem);
	void removePatientFromList(int id);
	PatientsListItem* findPatientInList(int id);
	
	void printPatientsList();
	void givePrescriptionsToPatient(int id);
	void removePrescriptionsFromPatient(int id);
	void givePrescriptionsToPatient(PatientsListItem* patientsListItem);
	void removePrescriptionsFromPatient(PatientsListItem* patientsListItem);
	int getPatientAttendingMedicalWorkerNo(PatientsListItem* patientsListItem);
	void printPatientMedicalRecords(int patientNo);
	void printPatientMedicalRecords(PatientsListItem* patientsListItem);
	const char* getDiagnosis(PatientsListItem* patientsListItem);

	float getAverageWorkloadPerMedicalWorker();
	void printInformation();
	Date& findNearestDischargeDate();
	const char* getDiagnosis(int diagnosisKey);
	bool isFull();

	void workWithUnit();
	void printInvitation();
	void choosePatient();
	void workWithPatient(int patientNo);
	void showWorkWithPatientInvitation();

	friend class Hospital;
};

