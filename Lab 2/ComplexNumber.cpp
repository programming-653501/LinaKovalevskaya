
#include "stdafx.h"
#include <math.h>


struct ComplexNumber
{
	double Re;
	double Im;
	double arg;
	double r;
	bool set = false;
};

int SkipUnwanted(void);
void EnterDouble(double* num);
void EnterInt(int* num);
void EnterNaturalExp(int* num);
void EnterComplex(ComplexNumber* Z);
void ResetComplex(ComplexNumber* Z);
void ShowRectForm(const ComplexNumber* Z);
void ShowExpForm(const ComplexNumber* Z);
void ConjugateComplex(ComplexNumber* Z);
void ShowConjComplex(ComplexNumber* Z);
void ExponentiateComplex(ComplexNumber* Z, unsigned exp);
void ShowExpComplex(ComplexNumber* Z);
void ShowLicenseInfo(void);
void ShowInvitation(void);


int main()
{
	ComplexNumber Z;
	int exit = 0, reset, choice;

	while (!exit)
	{
		printf("\nEnter a complex number:");
		EnterComplex(&Z);
		reset = 0;
		while (!reset)
		{
			ShowInvitation();
			EnterInt(&choice);
			switch (choice)
			{
			case 0: reset++; break;
			case 1: ShowRectForm(&Z); break;
			case 2:	ShowExpForm(&Z); break;
			case 3: ShowConjComplex(&Z); break;
			case 4:	ShowExpComplex(&Z); break;
			case 5: ShowLicenseInfo(); break;
			}
		}

		ResetComplex(&Z);
		printf("\nPress 0 - to continue with another number\n      1 - to exit\n");
		EnterInt(&exit);
	}

	return 0;
}


int SkipUnwanted(void)
{
	int ch, counter = 0;

	while ((ch = getchar()) != '\n')
		counter++;

	return counter;
}

void EnterDouble(double* num)
{
	int check = 0;

	while (!check)
	{
		check = scanf_s("%lf", num);
		if (!check)
		{
			printf("Input error. Re-enter, please.\n");
			SkipUnwanted();
		}
		else
			break;
	}
}

void EnterInt(int* num)
{
	int check = 0;

	while (!check)
	{
		check = scanf_s("%d", num);
		if (!check)
		{
			printf("Input error. Re-enter, please.\n");
			SkipUnwanted();
		}
		else
			break;
	}
}

void EnterNaturalExp(int *num)
{
	*num = 0;
	while (*num <= 0)
	{
		EnterInt(num);
		if (*num <= 0)
			printf("Only natural exponent allowed. Re-enter, please.\n");
	}
}

void EnterComplex(ComplexNumber* Z)
{
	if (Z->set)
		return;

	printf("\nRe = ");
	EnterDouble(&(Z->Re));
	printf("Im = ");
	EnterDouble(&(Z->Im));

	Z->r = sqrt(Z->Re*Z->Re + Z->Im*Z->Im);
	Z->arg = atan2(Z->Im, Z->Re);
	Z->set = true;
}

void ResetComplex(ComplexNumber* Z)
{
	Z->set = false;
}

void ShowRectForm(const ComplexNumber* Z)
{
	if (!Z->set)
		return;

	printf("\nRectangular form:");
	if (Z->Im >= 0)
		printf("\t%g + i*%g", Z->Re, Z->Im);
	else
		printf("\t%g - i*%g", Z->Re, -(Z->Im));
}

void ShowExpForm(const ComplexNumber* Z)
{
	if (!Z->set)
		return;

	printf("\nExponential form:");
	if (Z->Im >= 0)
		printf("\t%g*e^(i*%g)", Z->r, Z->Im);
	else
		printf("\t%g*e^(-i*%g)", Z->r, -(Z->Im));
}

void ConjugateComplex(ComplexNumber* Z)
{
	if (!Z->set)
		return;

	Z->Im = -(Z->Im);
}

void ShowConjComplex(ComplexNumber* Z)
{
	ConjugateComplex(Z);
	ShowRectForm(Z);
}

void ExponentiateComplex(ComplexNumber* Z, unsigned exp)
{
	if (!Z->set)
		return;

	Z->r = pow(Z->r, exp);
	Z->arg *= exp;
	Z->Re = Z->r * cos(Z->arg);
	Z->Im = Z->r * sin(Z->arg);
}

void ShowExpComplex(ComplexNumber* Z)
{
	if (!Z->set)
		return;

	int exp;

	printf("\nEnter an exponent: exp = ");
	EnterNaturalExp(&exp);
	ExponentiateComplex(Z, exp);
	ShowRectForm(Z);
}

void ShowLicenseInfo(void)
{
	const char LicenseInfo[] = "LicenseInfo\n\nLab2 2.1.11\n\nVersion: 1.0\nHeikeMyer, 2017. All rights reserved.";
	printf(LicenseInfo);
}

void ShowInvitation(void)
{
	printf("\n\nPress:");
	printf("\n\t0 - to quit work with your current number");
	printf("\n\t1 - to see the rectangular form of your current number");
	printf("\n\t2 - to see the exponential form of your current number");
	printf("\n\t3 - to conjugate your current number");
	printf("\n\t4 - to exponentiate your current number");
	printf("\n\t5 - to view the license information\n\n");
}

