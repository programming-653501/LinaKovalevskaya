
#include "Date.h"


void Date::enterDate()
{
	printf("Day: ");
	enterNaturalNumber(&day_);
	printf("Month: ");
	enterNaturalNumber(&month_);
	printf("Year: ");
	enterNaturalNumber(&year_);
}


Date& Date::chooseEarlierDate(Date& one, Date &another)
{
	return chooseEarlierYear(one, another);
}


Date& Date::chooseEarlierYear(Date& one, Date &another)
{
	return one.year_ < another.year_ ? one : (one.year_ > another.year_ ? another: chooseEarlierMonth(one, another));
}


Date& Date::chooseEarlierMonth(Date& one, Date &another)
{
	return one.month_ < another.month_ ? one : (one.month_ > another.month_ ? another : chooseEarlierDay(one, another));
}


Date& Date::chooseEarlierDay(Date& one, Date &another)
{
	return one.day_ < another.day_ ? one : (one.day_ > another.day_ ? another : one);
}


void Date::print()
{
	printf("%02d.%02d.%02d", day_, month_, year_);
}


void Date::addDaysSomehow(int offsetInDays)
{
	day_ += offsetInDays;
}

