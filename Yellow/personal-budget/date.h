#ifndef DATE_H
#define DATE_H

#include <chrono>
#include <string>

const int MonthsCount = 12;
const int DaysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int FebruaryInLeapYear = 29;

class Date {
public:
    Date(int new_year, int new_month, int new_day);
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    void operator++();
private:
    int year;
    int month;
    int day;
};

int GetDaysCount(int year, int month);
time_t AsTimestamp(const Date& date);
int ComputeDaysDiff(const Date& date_to, const Date& date_from);
Date DateFromString(const std::string& date);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
int operator-(const Date& lhs, const Date& rhs);

#endif // DATE_H
