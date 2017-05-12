#pragma once

#include "Functions.h"


class PrescriptionsListItem
{
private:

	PrescriptionsListItem* next;
	PrescriptionsListItem* previous;
	char prescription[MAX_PRESCRIPTION_LENGTH];

	void enterPrescription();

	friend class Patient;
};