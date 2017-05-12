#pragma once

#include "FullName.h"
#include "Date.h"


class ReceptionPatientForm
{
public:

	void fillIn();
	void enterAddress();	
	void computeDischargeDateSomehow();
	void print();

private:

	FullName fullName_;
	char address_[MAX_ADDRESS_LENGTH];
	Date dateOfBirth_;
	Date admissionDate_;
	Date dischargeDate_;

	void writeToFile(FILE* stream);
	void readFromFile(FILE* stream);

	friend class Patient;
};
