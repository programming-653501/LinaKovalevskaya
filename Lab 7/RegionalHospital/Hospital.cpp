
#include "Hospital.h"


Hospital::Hospital(const char* name, int hospitalNo)
{
	strncpy_s(externalDataFilePath_, DEFAULT_EXTERNAL_DATA_FILE_NAME, _MAX_PATH);

	strncpy_s(name_, name, MAX_HOSPITAL_NAME_LENGTH);
	hospitalNo_ = hospitalNo;

	initializeUnitsArray();
	
	capacity_ = currentPatientsAmount_ = 
	currentMedicalWorkersAmount_ = 0;

	strncpy_s(dataFilePath_, name_, _MAX_PATH);
}


Hospital::Hospital()
{
	strncpy_s(externalDataFilePath_, DEFAULT_EXTERNAL_DATA_FILE_NAME, _MAX_PATH);

	initializeUnitsArray();

	capacity_ = currentPatientsAmount_ =
		currentMedicalWorkersAmount_ = 0;
}


void Hospital::initializeUnitsArray()
{
	unitsAmount_ = 0;
	availableUnitsAmount_ = INITIAL_HOSPITAL_UNITS_AMOUNT;
	units_ = NULL;
}


void Hospital::increaseAvailableUnitsAmount()
{
	HospitalUnit* buffer = 
		new HospitalUnit[availableUnitsAmount_ * DYNAMIC_ARRAY_FACTOR];

	for (int i = 0; i < unitsAmount_; i++)
		buffer[i] = units_[i];

	delete[] units_;
	units_ = buffer;

	availableUnitsAmount_ *= DYNAMIC_ARRAY_FACTOR;
}


void Hospital::addUnit(const char* unitName, int unitCapacity)
{
	if (units_ == NULL)
		units_ = new HospitalUnit[availableUnitsAmount_];

	if (unitsAmount_ >= availableUnitsAmount_)
		increaseAvailableUnitsAmount();

	units_[unitsAmount_] = HospitalUnit(unitName, unitsAmount_ + 1, unitCapacity);
	unitsAmount_++;
}


void Hospital::computeCapacity()
{
	capacity_ = 0;
	for (int i = 0; i < unitsAmount_; i++)
		capacity_ += units_[i].capacity_;
}


void Hospital::computeCurrentPatientsAmount()
{
	currentPatientsAmount_ = 0;
	for (int i = 0; i < unitsAmount_; i++)
		currentPatientsAmount_ += units_[i].currentPatientsAmount_;
}


void Hospital::computeMedicalWorkersAmount()
{
	currentMedicalWorkersAmount_ = 0;
	for (int i = 0; i < unitsAmount_; i++)
		currentMedicalWorkersAmount_ += units_[i].currentMedicalWorkersAmount_;
}

Hospital::~Hospital()
{
	delete[] units_;
}


void Hospital::createHospitalDirectory()
{
	char* currentDirectory;

	if ((currentDirectory = _getcwd(NULL, 0)) == NULL)
	{
		printf("Can not find current directory.\n");
		exit(1);
	}

	createHospitalDirectoryPath(currentDirectory);

	if (!_mkdir(hospitalDirectoryPath_))
	{
		printf("Directory %s was successfully created.\n", hospitalDirectoryPath_);
	}
	else
	{
		printf("Can not create directory %s.\n", hospitalDirectoryPath_);
		exit(1);
	}
}


void Hospital::formDataFileName()
{
	formInnerFilePath(dataFilePath_, hospitalDirectoryPath_, name_);
}


void Hospital::formUnitDirectoriesFileName()
{
	formInnerFilePath(unitDirectoriesFilePath_, hospitalDirectoryPath_, 
					  DEFAULT_UNIT_DIRECTORIES_FILE_NAME);
}


void Hospital::formInnerFilesNames()
{
	formDataFileName();
	formUnitDirectoriesFileName();
}


void Hospital::createHospitalDirectoryPath(const char* currentDirectory)
{
	formSubdirectoryPath(hospitalDirectoryPath_, currentDirectory, name_);
}


void Hospital::writeDataToExternalFile()
{
	FILE* stream = NULL;

	stream = openStreamForWriting(stream, externalDataFilePath_);
	fwrite(name_, sizeof(char), MAX_HOSPITAL_NAME_LENGTH, stream);
	fwrite(dataFilePath_, sizeof(char), _MAX_PATH, stream);
	fwrite(unitDirectoriesFilePath_, sizeof(char), _MAX_PATH, stream);
	closeStream(stream, externalDataFilePath_);
}


void Hospital::readDataFromExternalFile()
{
	FILE* stream = NULL;

	stream = openStreamForReading(stream, externalDataFilePath_);
	fread(name_, sizeof(char), MAX_HOSPITAL_NAME_LENGTH, stream);
	fread(dataFilePath_, sizeof(char), _MAX_PATH, stream);
	fread(unitDirectoriesFilePath_, sizeof(char), _MAX_PATH, stream);
	closeStream(stream, externalDataFilePath_);
}


void Hospital::writeDataToFile()
{
	FILE* stream = NULL;
	stream = openStreamForWriting(stream, dataFilePath_);

	fwrite(name_, sizeof(char), MAX_HOSPITAL_NAME_LENGTH, stream);
	fwrite(&hospitalNo_, sizeof(int), 1, stream);
	fwrite(&unitsAmount_, sizeof(int), 1, stream);
	fwrite(&availableUnitsAmount_, sizeof(int), 1, stream);
	fwrite(&capacity_, sizeof(int), 1, stream);
	fwrite(&currentPatientsAmount_, sizeof(int), 1, stream);

	closeStream(stream, dataFilePath_);
}


void Hospital::readDataFromFile()
{
	FILE* stream = NULL;
	stream = openStreamForReading(stream, dataFilePath_);

	fread(name_, sizeof(char), MAX_HOSPITAL_NAME_LENGTH, stream);
	fread(&hospitalNo_, sizeof(int), 1, stream);
	fread(&unitsAmount_, sizeof(int), 1, stream);
	fread(&availableUnitsAmount_, sizeof(int), 1, stream);
	fread(&capacity_, sizeof(int), 1, stream);
	fread(&currentPatientsAmount_, sizeof(int), 1, stream);

	closeStream(stream, dataFilePath_);
}


void Hospital::writeUnitDirectoriesToFile()
{
	FILE* stream = NULL;
	stream = openStreamForWriting(stream, unitDirectoriesFilePath_);
	
	for (int i = 0; i < unitsAmount_; i++)
	{
		fwrite(&units_[i].unitNo_, sizeof(int), 1, stream);
		fwrite(units_[i].name_, sizeof(char), MAX_HOSPITAL_UNIT_NAME_LENGTH, stream);
		fwrite(units_[i].unitDirectoryPath_, sizeof(char), _MAX_PATH, stream);
		fwrite(units_[i].dataFilePath_, sizeof(char), _MAX_PATH, stream);
	}

	closeStream(stream, unitDirectoriesFilePath_);
}


void Hospital::readUnitDirectoriesFromFile()
{
	FILE* stream = NULL;
	stream = openStreamForReading(stream, unitDirectoriesFilePath_);

	for (int i = 0; i < unitsAmount_; i++)
	{
		fread(&units_[i].unitNo_, sizeof(int), 1, stream);
		fread(units_[i].name_, sizeof(char), MAX_HOSPITAL_UNIT_NAME_LENGTH, stream);
		fread(units_[i].unitDirectoryPath_, sizeof(char), _MAX_PATH, stream);
		fread(units_[i].dataFilePath_, sizeof(char), _MAX_PATH, stream);
	}

	closeStream(stream, unitDirectoriesFilePath_);
}


void Hospital::restoreHospitalFromFile()
{
	readDataFromExternalFile();
	readDataFromFile();

	units_ = new HospitalUnit[availableUnitsAmount_];

	readUnitDirectoriesFromFile();

	for (int i = 0; i < unitsAmount_; i++)
	{
		units_[i].readFromDataFile();
		units_[i].readDiagnosisDatabaseFromFile();
		units_[i].readMedicalWorkersFromFile();
		units_[i].readPatientsListFromFile();	
	}
}


void Hospital::writeHospitalToFile()
{

#if FIRST_RUN	
	createHospitalDirectory();
	formInnerFilesNames();
#endif

	for (int i = 0; i < unitsAmount_; i++)
	{

#if FIRST_RUN
		units_[i].createUnitDirectory(hospitalDirectoryPath_);
		units_[i].formInnerFilesPath();
#endif
		
		units_[i].writeToDataFile();
		units_[i].writeDiagnosisDatabaseToFile();
		units_[i].writeMedicalWorkersToFile();
		units_[i].writePatientsListToFile();
	}

	writeDataToFile();
	writeUnitDirectoriesToFile();
	writeDataToExternalFile();
}


void Hospital::chooseRandomDiagnosis(int& unitNo, int& diagnosisKey)
{
	unitNo = rand() % unitsAmount_ + 1;
	diagnosisKey = rand() % units_[unitNo - 1].currentDiagnosisDatabaseSize_ + 1;
}


void Hospital::admitPatient()
{
	my_fflush();
	int unitNo, diagnosisKey;

	chooseRandomDiagnosis(unitNo, diagnosisKey);
	printf("\n\nPatient is admitted to %s.", getUnitName(unitNo));
	printf(" Diagnosis: %s\n\n", getDiagnosisFromDatabase(unitNo, diagnosisKey));
	admitPatientToUnit(unitNo, diagnosisKey);
}


void Hospital::admitPatientToUnit(int unitNo, int diagnosisKey)
{
	if (isUnitFull(unitNo))
	{
		blowOffPatient(unitNo);
		return;
	}

	ReceptionPatientForm receptionPatientForm;
	signUpPatientAtReception(receptionPatientForm);

	referPatientToUnit(unitNo, receptionPatientForm, diagnosisKey);
}


void Hospital::blowOffPatient(int unitNo)
{
	Date nearestDischargeDate = units_[unitNo - 1].findNearestDischargeDate();
	printf("\nSorry, %s already operates at full capacity.\n", getUnitName(unitNo));
	printf("%s will be able to admit new patient ", getUnitName(unitNo));
	nearestDischargeDate.print();
}


void Hospital::signUpPatientAtReception(ReceptionPatientForm& receptionPatientForm)
{
	receptionPatientForm.fillIn();
	receptionPatientForm.computeDischargeDateSomehow();
}


bool Hospital::isUnitFull(int unitNo)
{
	return units_[unitNo - 1].isFull() ? true : false;
}


char* Hospital::getUnitName(int unitNo)
{
	return units_[unitNo - 1].name_;
}


void Hospital::referPatientToUnit(int unitNo, ReceptionPatientForm receptionPatientForm, int diagnosisKey)
{
	units_[unitNo - 1].addPatientToList(receptionPatientForm, diagnosisKey);
}


void Hospital::createDefaultHospital()
{
	strncpy_s(name_, "Kurt Cobain Memorial Hospital", MAX_HOSPITAL_NAME_LENGTH);

	addUnit("Therapeutic Unit", 4);	

	int index = 0;
	units_[index].addMedicalWorker("John", "Dorian", "intern", "attending physician");
	units_[index].addMedicalWorker("Perry", "Cox", "chief of medicine", "attending physician");

	FILE* stream;
	fopen_s(&stream, "_DefaultInternalDisiases.txt", "r");
	
	char buffer[MAX_DIAGNOSIS_LENGTH];
	while (!feof(stream))
	{
		fgets(buffer, MAX_DIAGNOSIS_LENGTH, stream);
		units_[index].addDiagnosisToDatabase(buffer);
	}
		
	fclose(stream);

	addUnit("Surgical Unit", 5);
	index++;

	units_[index].addMedicalWorker("Megan", "Hunt", "chief of surgery", "neurosurgeon");
	units_[index].addMedicalWorker("Carla", "Espinosa", "head nurse", "nurse");

	fopen_s(&stream, "_DefaultSurgicalDisiases.txt", "r");

	
	while (!feof(stream))
	{
		fgets(buffer, MAX_DIAGNOSIS_LENGTH, stream);
		units_[index].addDiagnosisToDatabase(buffer);
	}

	fclose(stream);

	addUnit("Psychiatric Unit", 6);
	index++;

	units_[index].addMedicalWorker("Hannibal", "Lecter", "psychotherapist", "psychiatrist");
	units_[index].addMedicalWorker("Alana", "Bloom", "professor of psychiatry", "psychiatrist");
	units_[index].addMedicalWorker("Bedelia", "Du Maurier", "psychotherapist", "psychiatrist");


	fopen_s(&stream, "_DefaultMentalDisorders.txt", "r");


	while (!feof(stream))
	{
		fgets(buffer, MAX_DIAGNOSIS_LENGTH, stream);
		units_[index].addDiagnosisToDatabase(buffer);
	}

	fclose(stream);
}


float Hospital::getAverageWorkloadPerMedicalWorker()
{
	return (float)currentPatientsAmount_ / currentMedicalWorkersAmount_;
}


float Hospital::getUnitAverageWorkloadPerMedicalWorker(int unitNo)
{
	return units_[unitNo - 1].getAverageWorkloadPerMedicalWorker();
}


void Hospital::printInformation()
{
	prepareAccount();
	printf("\nNo%d %s", hospitalNo_, name_);
	printf("\nNumber of units: %d\tCapacity: %d\tNumber of medical workers: %d\n", 
			unitsAmount_, capacity_, currentMedicalWorkersAmount_);

	for (int i = 0; i < unitsAmount_; i++)
		units_[i].printInformation();

	printf("\n\nCurrent number of patients in %s: %d", name_, currentPatientsAmount_);
	printf("\nAverage workload per medical worker: %.2f", getAverageWorkloadPerMedicalWorker());
}

void Hospital::prepareAccount()
{
	computeCapacity();
	computeCurrentPatientsAmount();
	computeMedicalWorkersAmount();
}


void Hospital::workWith()
{
	printInvitation();
	char choice = 0;
	bool flag = false;
	while (!flag)
	{
		printf("\nYour choice:\t");
		scanf_s("%c", &choice);
		switch (choice)
		{
		case '1': printInformation(); my_fflush();
			break;
		case '2': admitPatient(); my_fflush();
			break;
		case '3': chooseUnit(); 
				  printInvitation(); 
			break;
	
		case EXIT_KEY: flag = true; my_fflush();
			break;
		}
	}
}


bool Hospital::isUnitNoValid(int unitNo)
{
	return unitNo <= 0 ? false : (unitNo > unitsAmount_ ? false : true);
}


void Hospital::printInvitation()
{
	printf("\n\nHOSPITAL\nPress key:");
	printf("\n1 - view information about %s", name_);
	printf("\n2 - admit new patient");
	printf("\n3 - work with one of the units");
	printf("\n0 - exit\n");
}


void Hospital::chooseUnit()
{
	my_fflush();
	printf("Choose the unit you would like to work with:\n");
	printf("Enter unit's No:\t");
	int unitNo;
	enterNaturalNumber(&unitNo);
	if (isUnitNoValid(unitNo))
		units_[unitNo - 1].workWithUnit();
	else printf("\nNo such unitNo\n");
}


const char* Hospital::getDiagnosisFromDatabase(int unitNo, int diagnosisKey)
{
	return units_[unitNo - 1].getDiagnosis(diagnosisKey);
}