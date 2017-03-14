
#include "stdafx.h"
#include <conio.h>
#include <math.h>
#include <time.h>


const double E = 0.000000001;
int Iteration(double);
int Recursion(int, double, double);

int main()
{
	int iter, rec, start_time, end_time;
	double x;

	printf("x = ");
	scanf_s("%lf", &x);

	printf("\n%f\n", sin(x));
	printf("\nprecision = %.10f\n", E);

	start_time = clock();
	iter = Iteration(x);
	end_time = clock();
	printf("\nIteration took %d ms, %d steps\n", end_time-start_time, iter);

	start_time = clock();
	rec = Recursion(1, 0.0, x);
	end_time = clock();
	printf("\nRecursion took %d ms, %d steps\n", end_time-start_time, rec);

	_getch();
	return 0;
}

int Iteration(double x)
{
	double   sum = 0, standard = fabs(sin(x)), resid = 0.0;
	int i = 1, ed = 1, n = 0;

	do
	{
		double member = 1.0;
		for (int j = 1; j <= i; j++) {
			member *= (x / (double)j);
		}
		member *= ed;
		ed = -ed;
		sum += member;
		resid = fabs(standard - fabs(sum));
		n++;
		printf("\nn = %d\tstandard = %f\tsum = %f\tResid = %f\n", n, standard, sum, resid);
		i += 2;
	} while (resid > E);

	return n;
}

int Recursion(int n, double sum, double x)
{
	double standard = fabs(sin(x)), resid = 0.0, memb = 1.0;
	int lim = 2 * n - 1;

	for (int i = 1; i <= lim; i++) {
		memb *= (x / (double)i);
	}
	memb *= pow(-1, n - 1);
	sum += memb;
	resid = fabs(standard - fabs(sum));
	printf("\nn = %d\tstandard = %f\tsum = %f\tResid = %f\n", n, standard, sum, resid);

	if (resid <= E)
		return n;
	return Recursion(n + 1, sum, x);
}

