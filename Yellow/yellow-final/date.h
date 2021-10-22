#pragma once

#include <iostream>
#include <chrono>
#include <string>

class Date {
public:
    Date(int new_year, int new_month, int new_day);
    time_t AsTimestamp() const;

    const int year;
    const int month;
    const int day;
};

int ComputeDaysDiff(const Date& date_to, const Date& date_from);
Date DateFromString(const std::string& date);
Date ParseDate(std::istream& is);

std::ostream& operator<<(std::ostream& os, const Date& date);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
