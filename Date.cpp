#include <sstream>
#include <time.h>
#include "Date.h"

// Seconds in a given month. Non-leap year
int secondsPerMonth[12] = {
	3600 * 24 * 31, // january
	3600 * 24 * 28, // february
	3600 * 24 * 31,
	3600 * 24 * 30,
	3600 * 24 * 31,
	3600 * 24 * 30,
	3600 * 24 * 31,	// July
	3600 * 24 * 31, // August
	3600 * 24 * 30,
	3600 * 24 * 31,
	3600 * 24 * 30,
	3600 * 24 * 31	// December
};


// Default Constructor -- Initializes a Date object to the current date
Date::Date() {
	time_t current;
	time(&current);

	// Number of seconds in one astronomical year (365.25 days): 31557600
	this->year = 1970 + current / 31557600;

	this->month = 1;
	int s = current % 31557600; // s -> number of seconds in the current year
	for (int i = 0; (s - secondsPerMonth[i]) > 0 && i < 12; s -= secondsPerMonth[i], i++)
		month++;
	// s ~> number of seconds in the current month
	s -= 11 * 3600;	// Adjust for local time GMT + 1.
	this->day = 1 + s / (3600 * 24);

	//int hours = (s % (3600 * 24)) / 3600;
	//int minutes = (s % 3600) / 60;
}

Date::Date(string data) {
	stringstream str_in; char tmp;
	str_in.str(data);
	str_in >> this->day >> tmp >> this->month >> tmp >> this->year;
}

Date::Date(unsigned short int day, unsigned short int month, unsigned short int year) {
	this->day = day;
	this->month = month;
	this->year = year;
}

int Date::get_day() const {
	return day;
}

int Date::get_month() const {
	return month;
}

int Date::get_year() const {
	return year;
}

// Set Methods -- Necessary?
//void Date::set_day(int day) {
//	this->day = day;
//}
//
//void Date::set_month(int month) {
//	this->month = month;
//}
//
//void Date::set_year(int year) {
//	this->year = year;
//}


bool operator<=(const Date& d1, const Date& d2)
{
	if (d1.year < d2.year)
		return true;
	else if (d1.year == d2.year)
	{
		if (d1.month < d2.month)
			return true;
		else if (d1.month == d2.month)
			return d1.day <= d2.day;
		else
			return false;
	}
	else
		return false;

}

bool operator<(const Date& d1, const Date& d2)
{
	if (d1.year < d2.year)
		return true;
	else if (d1.year == d2.year)
	{
		if (d1.month < d2.month)
			return true;
		else if (d1.month == d2.month)
			return d1.day < d2.day;
		else
			return false;
	}
	else
		return false;

}


bool operator==(const Date& d1, const Date& d2)
{
	return d1.day == d2.day && d1.month == d2.month && d1.year == d2.year;
}


ostream& operator<<(ostream& out, const Date & date) {
	out << (date.day < 10 ? "0" : "") << date.day << '/' 
		<< (date.month < 10 ? "0" : "") << date.month << '/' << date.year;
	return out;
}

istream& operator>>(istream& in, Date& date) {
	char c;
	in >> date.day >> c >> date.month >> c >> date.year;

	return in;
}
