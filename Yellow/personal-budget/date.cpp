#include "date.h"

Date::Date(int new_year, int new_month, int new_day) {
    year = new_year;
    month = new_month;
    day = new_day;
}

int Date::GetYear() const {
    return year;
}

int Date::GetMonth() const {
    return month;
}

int Date::GetDay() const {
    return day;
}

void Date::operator++() {
    ++day;
    if(day > GetDaysCount(year, month)) {
        day = 1;
        ++month;
    }
    if(month > MonthsCount) {
        month = 1;
        ++year;
    }
}

void operator++(Date& d) {
    int year = d.GetYear();
    int month = d.GetMonth();
    int day = d.GetDay();

    ++day;
    if(day > GetDaysCount(year, month)) {
        day = 1;
        ++month;
    }
    if(month > MonthsCount) {
        month = 1;
        ++year;
    }
    d = {year, month, day};
}

int GetDaysCount(int year, int month)
{
    if(month == 2 && year%4 == 0) {
        return FebruaryInLeapYear;
    }
    return DaysInMonth[month-1];
}

bool operator==(const Date &lhs, const Date &rhs)
{
    return lhs.GetYear() == rhs.GetYear() &&
           lhs.GetMonth() == rhs.GetMonth() &&
           lhs.GetDay() == rhs.GetDay();
}
bool operator!=(const Date &lhs, const Date &rhs)
{
    return !(lhs == rhs);
}
bool operator<(const Date &lhs, const Date &rhs)
{
    if(lhs.GetYear() != rhs.GetYear()) {
        return lhs.GetYear() < rhs.GetYear();
    }
    if(lhs.GetMonth() != rhs.GetMonth()) {
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetDay() < rhs.GetDay();
}
bool operator>(const Date &lhs, const Date &rhs)
{
    if(lhs.GetYear() != rhs.GetYear()) {
        return lhs.GetYear() > rhs.GetYear();
    }
    if(lhs.GetMonth() != rhs.GetMonth()) {
        return lhs.GetMonth() > rhs.GetMonth();
    }
    return lhs.GetDay() > rhs.GetDay();
}
bool operator<=(const Date& lhs, const Date& rhs) {
    return lhs < rhs || lhs == rhs;
}
bool operator>=(const Date& lhs, const Date& rhs) {
    return lhs > rhs || lhs == rhs;
}

