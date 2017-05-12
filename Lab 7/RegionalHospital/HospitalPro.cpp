
#include "stdafx.h"
#include <conio.h>
#include <ctime>

#include "Hospital.h"


int main()
{
	srand(time(0));

#if !FIRST_RUN

	Hospital hospital;

	hospital.restoreHospitalFromFile();
	hospital.workWith();
	hospital.writeHospitalToFile();

#endif

#if FIRST_RUN

	Patient::setIdCounter(1);
	Hospital hospital;

	hospital.createDefaultHospital();
	hospital.workWith();
	hospital.writeHospitalToFile();

#endif

	_getch();
	return 0;
}
