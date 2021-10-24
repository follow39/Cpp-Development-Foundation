#pragma once

#include <iostream>
#include <chrono>
#include <string>

class Date {
public:
    Date(int new_year, int new_month, int new_day)
        : year(new_year),
          month(new_month),
          day(new_day) {}

    const int year;
    const int month;
    const int day;
};

Date DateFromString(const std::string& date);
Date ParseDate(std::istream& is);

std::ostream& operator<<(std::ostream& os, const Date& date);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
