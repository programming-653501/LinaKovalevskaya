#pragma once

#include "Functions.h"

class Date
{
public:

	static Date& chooseEarlierDate(Date& one, Date& another);

	Date() : day_(0), month_(0), year_(0) {}
	Date(int day, int month, int year): day_(day), month_(month), year_(year) {}

	void enterDate();
	void print();
	void addDaysSomehow(int offsetInDays);

private:

	int day_;
	int month_;
	int year_;

	static Date& chooseEarlierYear(Date& one, Date& another);
	static Date& chooseEarlierMonth(Date& one, Date& another);
	static Date& chooseEarlierDay(Date& one, Date& another);
};

