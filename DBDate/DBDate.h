#pragma once
#ifndef _DBDate_
#include <string>
#include <ostream>
#include <sstream>
using namespace std;
class DBDate {
	static const int arrDays[13];
	int day, month, year;
	friend ostream& operator<<(ostream& out, DBDate& date);
public:
	DBDate(string date);
	DBDate(int d, int m, int y);
	DBDate() :day(0), month(0), year(0) {};
	DBDate(DBDate& dat) :day(dat.day), month(dat.month), year(dat.year) {}
	int GetDay();
	int GetMonth();
	int GetYear();
	bool IsLeapYear(int year);
	int GetDaysInMonth(int month, int year);
	int DaysInCurYear();
	string dateToStr();
	bool operator==(DBDate& date);
	bool operator<(DBDate& date);
	bool operator>(DBDate& date);
	bool operator<= (DBDate& date);
	bool operator>= (DBDate& date);
	bool operator!= (DBDate& date);
	void operator+=(int days);
	void operator-=(int days);
	int operator-(DBDate& date);
};
#endif // !_DBDate_