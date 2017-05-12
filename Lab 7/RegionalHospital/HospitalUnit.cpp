
#include "HospitalUnit.h"


HospitalUnit::HospitalUnit(const char* name, int unitNo, int capacity)
{
	strncpy_s(name_, name, MAX_HOSPITAL_UNIT_NAME_LENGTH);
	unitNo_ = unitNo;
	capacity_ = capacity;

	initializeMedicalWorkersArray();
	initializeDiagnosisDatabase();
	initializePatientsList();
}


void HospitalUnit::initializePatientsList()
{
	currentPatientsAmount_ = 0;
	patientsListTail_ = patientsList_ = NULL;
}


void HospitalUnit::initializeDiagnosisDatabase()
{
	availableDiagnosisDatabaseSize_ = INITIAL_DIAGNOSIS_DATABASE_SIZE;
	currentDiagnosisDatabaseSize_ = 0;
	diagnosisDatabase_ = NULL;
}


void HospitalUnit::initializeMedicalWorkersArray()
{
	availableMedicalWorkersAmount_ = INITIAL_MEDICAL_WORKERS_AMOUNT;
	currentMedicalWorkersAmount_ = 0;
	medicalWorkers_ = NULL;
}


HospitalUnit::HospitalUnit()
{
	initializeMedicalWorkersArray();
	initializeDiagnosisDatabase();
	initializePatientsList();
}


void HospitalUnit::createUnitDirectory(const char* hospitalDirectory)
{
	formUnitDirectoryPath(hospitalDirectory);

	if (!_mkdir(unitDirectoryPath_))
	{
		printf("Directory %s was successfully created.\n", unitDirectoryPath_);
	}
	else
	{
		printf("Can not create directory %s.\n", unitDirectoryPath_);
		exit(1);
	}
}


void HospitalUnit::formUnitDirectoryPath(const char* hospitalDirectory)
{
	formSubdirectoryPath(unitDirectoryPath_, hospitalDirectory, name_);
}


void HospitalUnit::formDataFilePath()
{
	formInnerFilePath(dataFilePath_, unitDirectoryPath_, name_);
}


void HospitalUnit::formMedicalWorkersFilePath()
{
	formInnerFilePath(medicalWorkersFilePath_, unitDirectoryPath_, 
					  DEFAULT_MEDICAL_WORKERS_FILE_NAME);
}


void HospitalUnit::formDiagnosisDatabaseFilePath()
{
	formInnerFilePath(diagnosisDatabaseFilePath_, unitDirectoryPath_, 
					  DEFAULT_DIAGNOSIS_DATABASE_FILE_NAME);
}


void HospitalUnit::formPatientsListFilePath()
{
	formInnerFilePath(patientsListFilePath_, unitDirectoryPath_, 
					  DEFAULT_PATIENTS_FILE_NAME);
}


void HospitalUnit::formInnerFilesPath()
{
	formDataFilePath();
	formMedicalWorkersFilePath();
	formDiagnosisDatabaseFilePath();
	formPatientsListFilePath();
}


void HospitalUnit::writeToDataFile()
{
	FILE* stream = NULL;

	stream = openStreamForWriting(stream, dataFilePath_);

	if (stream == NULL)
		return;

	fwrite(name_, sizeof(char), MAX_HOSPITAL_UNIT_NAME_LENGTH, stream);
	fwrite(&unitNo_, sizeof(int), 1, stream);
	fwrite(&capacity_, sizeof(int), 1, stream);
	
	fwrite(&currentMedicalWorkersAmount_, sizeof(int), 1, stream);
	fwrite(&availableMedicalWorkersAmount_, sizeof(int), 1, stream);

	fwrite(&currentDiagnosisDatabaseSize_, sizeof(int), 1, stream);
	fwrite(&availableDiagnosisDatabaseSize_, sizeof(int), 1, stream);

	fwrite(medicalWorkersFilePath_, sizeof(char), _MAX_PATH, stream);
	fwrite(diagnosisDatabaseFilePath_, sizeof(char), _MAX_PATH, stream);
	fwrite(patientsListFilePath_, sizeof(char), _MAX_PATH, stream);

	closeStream(stream, dataFilePath_);
}


void HospitalUnit::readFromDataFile()
{
	FILE* stream = NULL;

	stream = openStreamForReading(stream, dataFilePath_);

	if (stream == NULL)
		return;

	fread(name_, sizeof(char), MAX_HOSPITAL_UNIT_NAME_LENGTH, stream);
	fread(&unitNo_, sizeof(int), 1, stream);
	fread(&capacity_, sizeof(int), 1, stream);

	fread(&currentMedicalWorkersAmount_, sizeof(int), 1, stream);
	fread(&availableMedicalWorkersAmount_, sizeof(int), 1, stream);

	fread(&currentDiagnosisDatabaseSize_, sizeof(int), 1, stream);
	fread(&availableDiagnosisDatabaseSize_, sizeof(int), 1, stream);

	fread(medicalWorkersFilePath_, sizeof(char), _MAX_PATH, stream);
	fread(diagnosisDatabaseFilePath_, sizeof(char), _MAX_PATH, stream);
	fread(patientsListFilePath_, sizeof(char), _MAX_PATH, stream);

	closeStream(stream, dataFilePath_);
}


void HospitalUnit::increaseMedicalWorkersAvailableAmount()
{
	MedicalWorker* buffer = 
		new MedicalWorker[availableMedicalWorkersAmount_ * DYNAMIC_ARRAY_FACTOR];

	for (int i = 0; i < currentMedicalWorkersAmount_; i++)
		buffer[i] = medicalWorkers_[i];

	delete[] medicalWorkers_;
	medicalWorkers_ = buffer;

	availableMedicalWorkersAmount_ *= DYNAMIC_ARRAY_FACTOR;
}


void HospitalUnit::addMedicalWorker(MedicalWorker* medicalWorker)
{
	if (medicalWorkers_ == NULL)
		medicalWorkers_ = new MedicalWorker[availableMedicalWorkersAmount_];

	if (currentMedicalWorkersAmount_ >= availableMedicalWorkersAmount_)
		increaseMedicalWorkersAvailableAmount();

	medicalWorkers_[currentMedicalWorkersAmount_] = *medicalWorker;
	currentMedicalWorkersAmount_++;
}


void HospitalUnit::addMedicalWorker(const char* name, const char* surname,
									const char* post, const char* speciality)
{
	MedicalWorker buffer(unitNo_, currentMedicalWorkersAmount_ + 1, name, surname, post, speciality);
	addMedicalWorker(&buffer);
}


HospitalUnit::~HospitalUnit()
{
	delete medicalWorkers_;
	delete diagnosisDatabase_;
	removePatientsList();
}


void HospitalUnit::writeMedicalWorkersToFile()
{
	FILE* stream = NULL;

	stream = openStreamForWriting(stream, medicalWorkersFilePath_);
	if (stream == NULL)
		return;

	fwrite(medicalWorkers_, sizeof(MedicalWorker), availableMedicalWorkersAmount_, stream);
	closeStream(stream, medicalWorkersFilePath_);
}


void HospitalUnit::readMedicalWorkersFromFile()
{
	FILE* stream = NULL;

	stream = openStreamForReading(stream, medicalWorkersFilePath_);
	if (stream == NULL)
		return;

	medicalWorkers_ = new MedicalWorker[availableMedicalWorkersAmount_];

	fread(medicalWorkers_, sizeof(MedicalWorker), availableMedicalWorkersAmount_, stream);
	closeStream(stream, medicalWorkersFilePath_);
}


void HospitalUnit::printMedicalWorkers()
{
	for (int i = 0; i < currentMedicalWorkersAmount_; i++)
		medicalWorkers_[i].printInformation();
}


void HospitalUnit::increaseDiagnosisDatabaseSize()
{
	Diagnosis* buffer = 
		new Diagnosis[availableDiagnosisDatabaseSize_*DYNAMIC_ARRAY_FACTOR];

	for (int i = 0; i < availableDiagnosisDatabaseSize_; i++)
		buffer[i] = diagnosisDatabase_[i];

	delete[] diagnosisDatabase_;
	diagnosisDatabase_ = buffer;

	availableDiagnosisDatabaseSize_ *= DYNAMIC_ARRAY_FACTOR;
}


void HospitalUnit::addDiagnosisToDatabase(const char* diagnosis)
{
	if (diagnosisDatabase_ == NULL)
		diagnosisDatabase_ = new Diagnosis[INITIAL_DIAGNOSIS_DATABASE_SIZE];
	
	if (currentDiagnosisDatabaseSize_ >= availableDiagnosisDatabaseSize_)
		increaseDiagnosisDatabaseSize();

	diagnosisDatabase_[currentDiagnosisDatabaseSize_] = 
		Diagnosis(diagnosis, unitNo_, currentDiagnosisDatabaseSize_ + 1);

	currentDiagnosisDatabaseSize_++;
}


void HospitalUnit::printDiagnosisDatabase()
{
	for (int i = 0; i < currentDiagnosisDatabaseSize_; i++)
		printf("%d %d %s", diagnosisDatabase_[i].hospitalUnitNo_, 
						   diagnosisDatabase_[i].key_, diagnosisDatabase_[i].diagnosis_);
}


void HospitalUnit::writeDiagnosisDatabaseToFile()
{
	FILE* stream = NULL;

	stream = openStreamForWriting(stream, diagnosisDatabaseFilePath_);
	if (stream == NULL)
		return;

	fwrite(diagnosisDatabase_, sizeof(Diagnosis), availableDiagnosisDatabaseSize_, stream);
	closeStream(stream, diagnosisDatabaseFilePath_);
}


void HospitalUnit::readDiagnosisDatabaseFromFile()
{
	FILE* stream = NULL;

	stream = openStreamForReading(stream, diagnosisDatabaseFilePath_);
	if (stream == NULL)
		return;

	diagnosisDatabase_ = new Diagnosis[availableDiagnosisDatabaseSize_];

	fread(diagnosisDatabase_, sizeof(Diagnosis), availableDiagnosisDatabaseSize_, stream);
	closeStream(stream, diagnosisDatabaseFilePath_);
}


void HospitalUnit::removePatientsList()
{
	PatientsListItem* buffer;
	while (patientsList_ != NULL)
	{
		buffer = patientsList_;
		patientsList_ = patientsList_->next;
		delete buffer;
	}
}


void HospitalUnit::addPatientToList(Patient* patient)
{
	PatientsListItem* patientsListItem = new PatientsListItem(*patient);

	patientsListItem->previous = patientsListItem->next = NULL;

	if (patientsList_ == NULL)
		patientsList_ = patientsListTail_ = patientsListItem;
	else
	{
		patientsListTail_->next = patientsListItem;
		patientsListItem->previous = patientsListTail_;
		patientsListTail_ = patientsListItem;
	}

	currentPatientsAmount_++;
}


MedicalWorker* HospitalUnit::findFreeMedicalWorkerSomehow()
{
	int minPatientsAmount = medicalWorkers_[0].currentPatientsAmount_,
		minPatientsAmountIndex = 0;

	for (int i = 0; i < currentMedicalWorkersAmount_; i++)
	{
		if (minPatientsAmount > medicalWorkers_[i].currentPatientsAmount_)
		{
			minPatientsAmount = medicalWorkers_[i].currentPatientsAmount_;
			minPatientsAmountIndex = i;
		}
	}
	
	return medicalWorkers_ + minPatientsAmountIndex;
}


void HospitalUnit::addPatientToList(ReceptionPatientForm& receptionPatientForm, int diagnosisKey)
{
	int medicalWorkerNo = (findFreeMedicalWorkerSomehow())->medicalWorkerNo_;

	addPatientToMedicalWorker(medicalWorkerNo);

	Patient buffer(unitNo_, receptionPatientForm, medicalWorkerNo);

	buffer.makeDiagnosis(diagnosisKey);
	addPatientToList(&buffer);
}


PatientsListItem* HospitalUnit::findPatientInList(int patientNo)
{
	PatientsListItem* buffer = patientsList_;

	while (buffer != NULL && buffer->patient.patientNo_ != patientNo)
		buffer = buffer->next;

	if (buffer == NULL)
		printf("\nCan not find a patient with such patientNo.\n");

	return buffer;
}


void HospitalUnit::removePatientFromList(int patientNo)
{
	PatientsListItem* patientsListItem = findPatientInList(patientNo);

	removePatientFromMedicalWorker(getPatientAttendingMedicalWorkerNo(patientsListItem));
	removePatientFromList(patientsListItem);
}


int HospitalUnit::getPatientAttendingMedicalWorkerNo(PatientsListItem* patientsListItem)
{
	if (patientsListItem == NULL)
		return 0;

	return patientsListItem->patient.medicalWorkerId_;
}


void HospitalUnit::removePatientFromList(PatientsListItem* patientsListItem)
{
	if (patientsListItem == NULL)
		return;

	if (patientsListItem->previous != NULL)
		patientsListItem->previous->next = patientsListItem->next;
	else
		patientsList_ = patientsListItem->next;

	if (patientsListItem->next != NULL)
		patientsListItem->next->previous = patientsListItem->previous;
	else
		patientsListTail_ = patientsListItem->previous;

	currentPatientsAmount_--;
	delete patientsListItem;
}


void HospitalUnit::writePatientsListToFile()
{
	FILE* stream = NULL;
	stream = openStreamForWriting(stream, patientsListFilePath_);
	if (stream == NULL)
		return;

	Patient::writeIdCounterToFile(stream);
	fwrite(&currentPatientsAmount_, sizeof(int), 1, stream);
	writePatientsListToFile(stream);
	closeStream(stream, patientsListFilePath_);
}


void HospitalUnit::writePatientsListToFile(FILE* stream)
{
	if (stream == NULL)
		return;

	PatientsListItem* buffer = new PatientsListItem;
	
	buffer = patientsList_;
	while (buffer != NULL)
	{
		buffer->patient.writeToFile(stream);
		buffer = buffer->next;
	}

	delete buffer;
}


void HospitalUnit::readPatientsListFromFile()
{
	FILE* stream = NULL;

	stream = openStreamForReading(stream, patientsListFilePath_);

	Patient::readIdCounterFromFile(stream);
	readPatientsListFromFile(stream);

	closeStream(stream, patientsListFilePath_);
}


void HospitalUnit::readPatientsListFromFile(FILE* stream)
{
	if (stream == NULL)
		return;

	int restoredCurrentPatientsAmount;
	fread(&restoredCurrentPatientsAmount, sizeof(int), 1, stream);

	for (int i = 0; i < restoredCurrentPatientsAmount; i++)
	{
		Patient buffer;
		buffer.readFromFile(stream);
		addPatientToList(&buffer);
	}
}


void HospitalUnit::printPatientsList()
{
	PatientsListItem* buffer = new PatientsListItem;

	buffer = patientsList_;
	while (buffer != NULL)
	{
		printPatientMedicalRecords(buffer);
		buffer = buffer->next;
	}

	delete buffer;
}


const char* HospitalUnit::getDiagnosis(PatientsListItem* patientsListItem)
{
	return diagnosisDatabase_[patientsListItem->patient.diagnosisKey_ - 1].diagnosis_;
}


bool HospitalUnit::isFull()
{
	return currentPatientsAmount_ >= capacity_ ? true : false;
}


void HospitalUnit::addPatientToMedicalWorker(int medicalWorkerNo)
{
	medicalWorkers_[medicalWorkerNo - 1].increaseCurrentPatientsAmount();
}


void HospitalUnit::removePatientFromMedicalWorker(int medicalWorkerNo)
{
	if (medicalWorkerNo <= 0)
		return;
	medicalWorkers_[medicalWorkerNo - 1].decreaseCurrentPatientsAmount();
}


void HospitalUnit::givePrescriptionsToPatient(int id)
{
	PatientsListItem* buffer = findPatientInList(id);
	if (buffer == NULL)
		return;

	givePrescriptionsToPatient(buffer);
}


void HospitalUnit::removePrescriptionsFromPatient(int id)
{
	PatientsListItem* buffer = findPatientInList(id);
	if (buffer == NULL)
		return;

	removePrescriptionsFromPatient(buffer);
}


void HospitalUnit::givePrescriptionsToPatient(PatientsListItem* patientsListItem)
{
	char buf[MAX_PRESCRIPTION_LENGTH];

	char choice = 0;
	while (choice != '0')
	{
		my_fflush();
		printf("Prescription to recommend: ");
		if (!my_fgets(buf, MAX_PRESCRIPTION_LENGTH))
			my_fflush();
		patientsListItem->patient.addPrescriptionToList(buf);
		printf("Press '0' to exit or any other key to go on.\t");
		scanf_s("%c", &choice);
	}
}


void HospitalUnit::removePrescriptionsFromPatient(PatientsListItem* patientsListItem)
{
	char buf[MAX_PRESCRIPTION_LENGTH];

	char choice = 0;
	while (choice != '0')
	{
		my_fflush();
		printf("Prescription to cancel: ");
		if (!my_fgets(buf, MAX_PRESCRIPTION_LENGTH))
			my_fflush();
		patientsListItem->patient.removePrescriptionFromList(buf);
		printf("Press '0' to exit or any other key to go on.\t");
		scanf_s("%c", &choice);
	}
}


float HospitalUnit::getAverageWorkloadPerMedicalWorker()
{
	return (float)currentPatientsAmount_ / currentMedicalWorkersAmount_;
}


void HospitalUnit::printPatientMedicalRecords(PatientsListItem* patientsListItem)
{
	if (patientsListItem == NULL)
		return;

	printf("\nMedical Records:\n");
	printf("\nNo%d\t", patientsListItem->patient.patientNo_);
	patientsListItem->patient.printReceptionForm();
	printf("\nDiagnosis: %s", getDiagnosis(patientsListItem));
	printf("\nAttending medical worker:\t");
	printMedicalWorker(getPatientAttendingMedicalWorkerNo(patientsListItem));
	patientsListItem->patient.printPrescriptionsList();
}


void HospitalUnit::printPatientMedicalRecords(int patientNo)
{
	PatientsListItem* buffer = findPatientInList(patientNo);
	printPatientMedicalRecords(buffer);
}


void HospitalUnit::printInformation()
{
	printf("\nNo%d %s", unitNo_, name_);
	printf("\nCapacity: %d\tNumber of medical workers: %d", capacity_, currentMedicalWorkersAmount_);
	printf("\nCurrent number of patients in %s: %d", name_, currentPatientsAmount_);
	printf("\nAverage workload per medical worker: %.2f", getAverageWorkloadPerMedicalWorker());
}


void HospitalUnit::printMedicalWorker(int medicalWorkerNo)
{
	medicalWorkers_[medicalWorkerNo - 1].printInformation();
}


void HospitalUnit::workWithUnit()
{
	printInvitation();
	char choice = 0;
	bool flag = false;
	while (!flag)
	{
		my_fflush();
		printf("\nYour choice:\t");
		scanf_s("%c", &choice);
		switch (choice)
		{
		case '1': printInformation(); 
			break;
		case '2': printMedicalWorkers(); 
			break;
		case '3': printDiagnosisDatabase(); 
			break;
		case '4': printPatientsList(); 
			break;
		case '5': choosePatient(); 
				  printInvitation();
			break;
		case EXIT_KEY: flag = true; my_fflush();
			break;
		}
	}
}


void HospitalUnit::printInvitation()
{
	printf("\n\nHOSPITAL UNIT\nPress key:");
	printf("\n1 - view information about %s", name_);
	printf("\n2 - view information about current medical workers");
	printf("\n3 - view %s diagnosis database", name_);
	printf("\n4 - view list of current patients");
	printf("\n5 - work with one of the patients");
	printf("\n0 - exit\n");
}


void HospitalUnit::choosePatient()
{
	printf("\nChoose the patient you would like to work with:\n");
	printf("Enter patient's No:\t");
	int patientNo;
	enterNaturalNumber(&patientNo);
	
	workWithPatient(patientNo);
}


void HospitalUnit::showWorkWithPatientInvitation()
{
	printf("\n\nWORK WITH PATIENT\nPress key:");
	printf("\n1 - view patient's medical records");
	printf("\n2 - discharge patient");
	printf("\n3 - give prescriptions to patient", name_);
	printf("\n4 - cancel some of the patient's prescriptions");
	printf("\n0 - exit\n");
}


void HospitalUnit::workWithPatient(int patientNo)
{
	showWorkWithPatientInvitation();
	char choice = 0;
	bool flag = false;
	while (!flag)
	{
		my_fflush();
		printf("Your choice:\t");
		scanf_s("%c", &choice);
		switch (choice)
		{
		case '1': printPatientMedicalRecords(patientNo); 
			break;
		case '2': removePatientFromList(patientNo); 
			break;
		case '3': my_fflush();  
				  givePrescriptionsToPatient(patientNo); 
				  showWorkWithPatientInvitation();
			break;
		case '4': my_fflush(); 
				  removePrescriptionsFromPatient(patientNo); 
				  showWorkWithPatientInvitation();
			break;
		case EXIT_KEY: flag = true; 
			break;
		}
	}
}


Date& HospitalUnit::findNearestDischargeDate()
{
	PatientsListItem* buffer = new PatientsListItem;

	Date nearestDischargeDate = patientsList_->patient.getDischargeDate();
	buffer = patientsList_;
	while (buffer != NULL)
	{
		nearestDischargeDate = 
			Date::chooseEarlierDate(nearestDischargeDate, buffer->patient.getDischargeDate());
		buffer = buffer->next;
	}

	delete buffer;

	return nearestDischargeDate;
}


const char* HospitalUnit::getDiagnosis(int diagnosisKey)
{
	return diagnosisDatabase_[diagnosisKey - 1].diagnosis_;
}


