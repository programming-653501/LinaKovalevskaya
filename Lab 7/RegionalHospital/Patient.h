#pragma once

#include "ReceptionPatientForm.h"
#include "Diagnosis.h"
#include "PrescriptionsListItem.h"


class Patient
{
public:

	static int idCounter;
	static void setIdCounter(int counter);
	static int getIdCounter();

private:
	
	static void increaseIdCounter();
	static void writeIdCounterToFile(FILE* stream);
	static void readIdCounterFromFile(FILE* stream);
	
	Patient();
	Patient(int hospitalUnitId, int key, int medicalWorkerId);
	Patient(int hospitalUnitId, ReceptionPatientForm& receptionPatientForm, int medicalWorkerNo);
	Patient(Patient& other);
	~Patient();

	int patientNo_;
	ReceptionPatientForm receptionPatientForm_;
	int hospitalUnitId_;	
	int diagnosisKey_;
	int medicalWorkerId_;

	int prescriptionsAmount_;
	PrescriptionsListItem* prescriptionsList_;
	PrescriptionsListItem* prescriptionsListTail_;
	void initializePrescriptionsList();

	void addPrescriptionToList(const char* prescription);
	void removePrescriptionFromList(PrescriptionsListItem* patientsListItem);
	void removePrescriptionFromList(const char* prescription);
	PrescriptionsListItem* findPrescriptionInList(const char* prescription);
	void removePrescriptionsList();
	void printPrescriptionsList();
	void writePrescriptionsListToFile(FILE* stream);
	void readPrescriptionsListFromFile(FILE* stream);
	void copyPrescriptionsList(Patient& other);

	void printReceptionForm();
	void writeToFile(FILE* stream);
	void readFromFile(FILE* stream);

	Date& getDischargeDate();
	void makeDiagnosis(int diagnosisKey);

	friend class HospitalUnit;
	friend class PatientsListItem;	
};


