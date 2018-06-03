#include <cstring>
#include "DBDate.h"

ostream &operator<<(ostream &out, DBDate &date) { //friend func
    out << date.day << "." << date.month << "." << date.year;
    return out;
}

string DBDate::dateToStr() {
    stringstream ss;
    ss << day << "|" << month << "|" << year;
    return ss.str();
}

DBDate::DBDate(string date) {
    char *delims = ".", *token;
    token = (char *) date.c_str();
    day = atoi(strtok(token, delims));
    month = atoi(strtok(nullptr, delims));
    year = atoi(strtok(nullptr, delims));
}

DBDate::DBDate(int d, int m, int y) : day(d), month(m), year(y) {}

int DBDate::GetDay() { return day; }

int DBDate::GetMonth() { return month; }

int DBDate::GetYear() { return year; }

bool DBDate::IsLeapYear(int year) {
    return (1 - (year % 4 + 2) / (year % 4 + 1)) * ((year % 100 + 2) * (year % 100 + 1)) +
           (1 - ((year % 400 + 2) / (year % 400 + 1))) ? true : false;
}

int DBDate::GetDaysInMonth(int month, int year) {
    return 28 + ((month + (month / 8)) % 2) + 2 % month + ((1 + (1 - (year % 4 + 2) % (year % 4 + 1)) *
                                                            ((year % 100 + 2) % (year % 100 + 1))
                                                            + (1 - (year % 400 + 2) % (year % 400 + 1))) / month) + (1 / month) -
           (((1 - (year % 4 + 2) % (year % 4 + 1)) * ((year % 100 + 2) % (year % 100 + 1)) + (1 - (year % 400 + 2) % (year % 400 + 1))) / month);
    //int leapYear[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
    //int simpleYear[12] = { 31,28,31,30,31,30,31,31,30,31,30,31};
}

int DBDate::DaysInCurYear() {
    int days = 0;
    for (int i = 0; i < month; i++) {
        days += GetDaysInMonth(i + 1, year);
    }
    return days;
}

bool DBDate::operator==(DBDate &date) {
    return ((date.day == day) && (date.month == month) && (date.year == year)) ? true : false;
}

bool DBDate::operator<(DBDate &date) {
    int sum1 = year * (IsLeapYear(year) ? 366 : 365) + month * GetDaysInMonth(month, year) + day;
    int sum2 = date.year * (IsLeapYear(date.year) ? 366 : 365) + date.month * GetDaysInMonth(date.month, date.year) +
               date.day;
    return (sum1 < sum2) ? true : false;
}

bool DBDate::operator<=(DBDate &date) {
    return ((*this) == date || (*this) < date);
}

bool DBDate::operator>(DBDate &date) {
    return !((*this) <= date);
}

bool DBDate::operator>=(DBDate &date) {
    return ((*this) == date || (*this) > date);
}

bool DBDate::operator!=(DBDate &date) {
    return !((*this) == date);
}

void DBDate::operator+=(int days) {
    while (days != 0) {
        int daysInMonth = GetDaysInMonth(month, year);
        if (days <= daysInMonth - day) {
            day += days;
        } else {
            days -= daysInMonth - day;
            day = 0;
            if (month == 12) {
                month = 1;
                year++;
            } else month++;
        }
    }
}

void DBDate::operator-=(int days) {
    while (days != 0) {
        if (days < day) {
            day -= days;
        } else {
            days -= day;
            if (month == 1) {
                month = 12;
                year--;
            } else month--;
            day = GetDaysInMonth(month, year);
        }
    }
}

int DBDate::operator-(DBDate &date1) {
    int sum1 = year * (IsLeapYear(year) ? 366 : 365) + month * GetDaysInMonth(month, year) + day;
    int sum2 =
            date1.year * (IsLeapYear(date1.year) ? 366 : 365) + date1.month * GetDaysInMonth(date1.month, date1.year) +
            date1.day;
    return sum1 - sum2;
}