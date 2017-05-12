
#include "ReceptionPatientForm.h"


void ReceptionPatientForm::fillIn()
{
	printf("\nFill in reception form:\n");
	fullName_.enterFullName();
	enterAddress();
	printf("Birth date\n");
	dateOfBirth_.enterDate();
	printf("Admission date\n");
	admissionDate_.enterDate();
	my_fflush();
}


void ReceptionPatientForm::enterAddress()
{
	printf("Address: ");
	if (!my_fgets(address_, MAX_ADDRESS_LENGTH))
		my_fflush();
}


void ReceptionPatientForm::print()
{
	printf("Full name: ");
	fullName_.print();
	printf("\n%s\n", address_);
	printf("Date of birth: ");
	dateOfBirth_.print();
	printf("\nAdmission date: ");
	admissionDate_.print();
	printf("\nDischarge date: ");
	dischargeDate_.print();
}


void ReceptionPatientForm::computeDischargeDateSomehow()
{
	dischargeDate_ = admissionDate_;
	dischargeDate_.addDaysSomehow(MAX_ADMISSION_PERIOD);
}


void ReceptionPatientForm::writeToFile(FILE* stream)
{
	if (stream == NULL)
		return;

	fwrite(this, sizeof(ReceptionPatientForm), 1, stream);
}


void ReceptionPatientForm::readFromFile(FILE* stream)
{
	if (stream == NULL)
		return;

	fread(this, sizeof(ReceptionPatientForm), 1, stream);
}
