
#include "Patient.h"


int Patient::idCounter;


Patient::Patient(int hospitalUnitId, int patientNo, int medicalWorkerId)
{
	hospitalUnitId_ = hospitalUnitId;
	patientNo_ = patientNo;
	medicalWorkerId_ = medicalWorkerId;
	initializePrescriptionsList();
}


Patient::Patient()
{
	initializePrescriptionsList();
}


void Patient::initializePrescriptionsList()
{
	prescriptionsList_ = prescriptionsListTail_ = NULL;
	prescriptionsAmount_ = 0;
}


Patient::~Patient()
{
	removePrescriptionsList();
}


void Patient::removePrescriptionsList()
{
	PrescriptionsListItem* buffer;
	while (prescriptionsList_ != NULL)
	{
		buffer = prescriptionsList_;
		prescriptionsList_ = prescriptionsList_->next;
		delete buffer;
	}
	prescriptionsAmount_ = 0;
}


void Patient::addPrescriptionToList(const char* prescription)
{
	PrescriptionsListItem* prescriptionsListItem = new PrescriptionsListItem;

	prescriptionsListItem->previous = prescriptionsListItem->next = NULL;
	strncpy_s(prescriptionsListItem->prescription, prescription, MAX_PRESCRIPTION_LENGTH-1);

	if (prescriptionsList_ == NULL)		
		prescriptionsList_ = prescriptionsListTail_ = prescriptionsListItem;

	else
	{
		prescriptionsListTail_->next = prescriptionsListItem;
		prescriptionsListItem->previous = prescriptionsListTail_;
		prescriptionsListTail_ = prescriptionsListItem;
	}

	prescriptionsAmount_++;
}


PrescriptionsListItem* Patient::findPrescriptionInList(const char* prescription)
{
	PrescriptionsListItem* buffer = prescriptionsList_;

	while (buffer != NULL && strcmp(prescription, buffer->prescription))
		buffer = buffer->next;

	return buffer;
}


void Patient::removePrescriptionFromList(PrescriptionsListItem* prescriptionsListItem)
{
	if (prescriptionsListItem == NULL)
		return;

	if (prescriptionsListItem->previous != NULL)
		prescriptionsListItem->previous->next = prescriptionsListItem->next;
	else
		prescriptionsList_ = prescriptionsListItem->next;

	if (prescriptionsListItem->next != NULL)
		prescriptionsListItem->next->previous = prescriptionsListItem->previous;
	else
		prescriptionsListTail_ = prescriptionsListItem->previous;

	prescriptionsAmount_--;
	delete prescriptionsListItem;
}


void Patient::printPrescriptionsList()
{
	PrescriptionsListItem* buffer = new PrescriptionsListItem;

	printf("\nPrescriptions:");
	buffer = prescriptionsList_;
	while (buffer != NULL)
	{
		printf("%s\n", buffer->prescription);
		buffer = buffer->next;
	}
	delete buffer;
}


void Patient::removePrescriptionFromList(const char* prescription)
{
	PrescriptionsListItem* prescriptionsListItem = findPrescriptionInList(prescription);
	removePrescriptionFromList(prescriptionsListItem);
}


Patient::Patient(int hospitalUnitId, ReceptionPatientForm& receptionPatientForm, int medicalWorkerNo)
{
	hospitalUnitId_ = hospitalUnitId;

	patientNo_ = idCounter;
	increaseIdCounter();

	receptionPatientForm_ = receptionPatientForm;	

	medicalWorkerId_ = medicalWorkerNo;

	initializePrescriptionsList();
}


void Patient::makeDiagnosis(int diagnosisKey)
{
	diagnosisKey_ = diagnosisKey;
}


void Patient::printReceptionForm()
{
	receptionPatientForm_.print();
}


void Patient::writePrescriptionsListToFile(FILE* stream)
{
	if (stream == NULL)
		return;

	fwrite(&prescriptionsAmount_, sizeof(int), 1, stream);

	PrescriptionsListItem* buffer = new PrescriptionsListItem;

	buffer = prescriptionsList_;
	while (buffer != NULL)
	{
		fwrite(&buffer->prescription, sizeof(char), MAX_PRESCRIPTION_LENGTH, stream);
		buffer = buffer->next;
	}

	delete buffer;
}


void Patient::readPrescriptionsListFromFile(FILE* stream)
{
	if (stream == NULL)
		return;

	int prescriptionsAmount;
	fread(&prescriptionsAmount, sizeof(int), 1, stream);
	
	for (int i=0; i<prescriptionsAmount; i++)
	{
		char buffer[MAX_PRESCRIPTION_LENGTH];
		fread(&buffer, sizeof(char), MAX_PRESCRIPTION_LENGTH, stream);
		addPrescriptionToList(buffer);
	}
}


void Patient::writeToFile(FILE* stream)
{
	if (stream == NULL)
		return;

	fwrite(&patientNo_, sizeof(int), 1, stream);
	receptionPatientForm_.writeToFile(stream);

	fwrite(&hospitalUnitId_, sizeof(int), 1, stream);
	fwrite(&diagnosisKey_, sizeof(int), 1, stream);
	fwrite(&medicalWorkerId_, sizeof(int), 1, stream);
	
	writePrescriptionsListToFile(stream);
}


void Patient::readFromFile(FILE* stream)
{
	if (stream == NULL)
		return;

	fread(&patientNo_, sizeof(int), 1, stream);
	receptionPatientForm_.readFromFile(stream);

	fread(&hospitalUnitId_, sizeof(int), 1, stream);
	fread(&diagnosisKey_, sizeof(int), 1, stream);
	fread(&medicalWorkerId_, sizeof(int), 1, stream);

	readPrescriptionsListFromFile(stream);
}


Patient::Patient(Patient& other)
{
	receptionPatientForm_ = other.receptionPatientForm_;
	hospitalUnitId_ = other.hospitalUnitId_;
	patientNo_ = other.patientNo_;
	medicalWorkerId_ = other.medicalWorkerId_;
	diagnosisKey_ = other.diagnosisKey_;
	initializePrescriptionsList();

	copyPrescriptionsList(other);
}


void Patient::copyPrescriptionsList(Patient& other)
{
	removePrescriptionsList();
	PrescriptionsListItem* buffer = new PrescriptionsListItem;

	buffer = other.prescriptionsList_;
	while (buffer != NULL)
	{
		addPrescriptionToList(buffer->prescription);
		buffer = buffer->next;
	}

	delete buffer; 
}


void Patient::setIdCounter(int counter)
{
	idCounter = counter;
}


int Patient::getIdCounter()
{
	return idCounter;
}


void Patient::increaseIdCounter()
{
	idCounter++;
}


void Patient::writeIdCounterToFile(FILE* stream)
{
	if (stream == NULL)
		return;

	fwrite(&idCounter, sizeof(int), 1, stream);
}


void Patient::readIdCounterFromFile(FILE* stream)
{
	if (stream == NULL)
		return;

	fread(&idCounter, sizeof(int), 1, stream);
}


Date& Patient::getDischargeDate()
{
	return receptionPatientForm_.dischargeDate_;
}