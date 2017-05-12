
#include "PrescriptionsListItem.h"


void PrescriptionsListItem::enterPrescription()
{
	printf("Prescription: ");
	if (!my_fgets(prescription, MAX_PRESCRIPTION_LENGTH))
		my_fflush();
}