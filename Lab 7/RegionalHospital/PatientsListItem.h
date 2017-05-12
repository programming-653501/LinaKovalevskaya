#pragma once

#include "Patient.h"

class PatientsListItem
{
private:

	PatientsListItem* next;
	PatientsListItem* previous;
	Patient patient;

	PatientsListItem() {};
	PatientsListItem(Patient& other) : patient(other) {}

	friend class HospitalUnit;
};
