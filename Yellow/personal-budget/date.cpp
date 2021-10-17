#include "date.h"
#include <sstream>

using namespace std;

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

int GetDaysCount(int year, int month)
{
    if(month == 2 && year%4 == 0) {
        return FebruaryInLeapYear;
    }
    return DaysInMonth[month-1];
}

time_t AsTimestamp(const Date& date) {
    tm t;
    t.tm_sec  = 0;
    t.tm_min  = 0;
    t.tm_hour = 0;
    t.tm_mday = date.GetDay();
    t.tm_mon  = date.GetMonth() - 1;
    t.tm_year = date.GetYear() - 1900;
    t.tm_isdst = 0;
    return mktime(&t);
}

int ComputeDaysDiff(const Date& date_to, const Date& date_from) {
    const time_t timestamp_to = AsTimestamp(date_to);
    const time_t timestamp_from = AsTimestamp(date_from);
    static constexpr int SECONDS_IN_DAY = 60 * 60 * 24;
    return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

Date DateFromString(const string& date) {
    stringstream ss(date);
    int year = 0;
    int month = 0;
    int day = 0;
    char ch1 = 0;
    char ch2 = 0;

    ss >> year >> ch1 >> month >> ch2 >> day;

    return {year, month, day};
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

int operator-(const Date &lhs, const Date &rhs)
{
    return 0;
}
