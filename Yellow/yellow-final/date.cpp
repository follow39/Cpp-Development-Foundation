#include "date.h"
#include <sstream>
#include <iomanip>

using namespace std;

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

Date ParseDate(std::istream &is)
{
    string temp;
    is >> temp;
    return DateFromString(temp);
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    char prev = os.fill('0');
    os << setw(4) << date.year << '-' <<
          setw(2) << date.month << '-' <<
          setw(2) << date.day;
    os.fill(prev);
    return os;
}

bool operator==(const Date &lhs, const Date &rhs)
{
    return lhs.year == rhs.year &&
           lhs.month == rhs.month &&
           lhs.day == rhs.day;
}

bool operator!=(const Date &lhs, const Date &rhs)
{
    return lhs.year != rhs.year ||
           lhs.month != rhs.month ||
           lhs.day != rhs.day;
}

bool operator<(const Date &lhs, const Date &rhs)
{
    if(lhs.year != rhs.year) {
        return lhs.year < rhs.year;
    } else if(lhs.month != rhs.month) {
        return lhs.month < rhs.month;
    }
    return lhs.day < rhs.day;
}

bool operator>(const Date& lhs, const Date& rhs) {
    if(lhs.year != rhs.year) {
        return lhs.year > rhs.year;
    } else if(lhs.month != rhs.month) {
        return lhs.month > rhs.month;
    }
    return lhs.day > rhs.day;
}

bool operator<=(const Date& lhs, const Date& rhs) {
    if(lhs.year != rhs.year) {
        return lhs.year <= rhs.year;
    } else if(lhs.month != rhs.month) {
        return lhs.month <= rhs.month;
    }
    return lhs.day <= rhs.day;
}
bool operator>=(const Date& lhs, const Date& rhs) {
    if(lhs.year != rhs.year) {
        return lhs.year >= rhs.year;
    } else if(lhs.month != rhs.month) {
        return lhs.month >= rhs.month;
    }
    return lhs.day >= rhs.day;
}
