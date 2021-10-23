#include "date.h"
#include <sstream>
#include <iomanip>

using namespace std;

Date::Date(int new_year, int new_month, int new_day)
    : year(new_year),
      month(new_month),
      day(new_day) {}

Date::Date(const Date& new_date)
    : year(new_date.year),
      month(new_date.month),
      day(new_date.day) {}

time_t Date::AsTimestamp() const {
    tm t;
    t.tm_sec  = 0;
    t.tm_min  = 0;
    t.tm_hour = 0;
    t.tm_mday = day;
    t.tm_mon  = month - 1;
    t.tm_year = year - 1900;
    t.tm_isdst = 0;
    return mktime(&t);
}

int ComputeDaysDiff(const Date& date_to, const Date& date_from) {
    const time_t timestamp_to = date_to.AsTimestamp();
    const time_t timestamp_from = date_from.AsTimestamp();
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
//    return lhs.AsTimestamp() == rhs.AsTimestamp();
    return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

bool operator!=(const Date &lhs, const Date &rhs)
{
//    return lhs.AsTimestamp() != rhs.AsTimestamp();
    return lhs.year != rhs.year || lhs.month != rhs.month || lhs.day != rhs.day;
}

bool operator<(const Date &lhs, const Date &rhs)
{
//    return lhs.AsTimestamp() < rhs.AsTimestamp();
    if(lhs.year != rhs.year) {
        return lhs.year < rhs.year;
    } else if(lhs.month != rhs.month) {
        return lhs.month < rhs.month;
    }
    return lhs.day < rhs.day;
}

bool operator>(const Date& lhs, const Date& rhs) {
//    return lhs.AsTimestamp() > rhs.AsTimestamp();
    if(lhs.year != rhs.year) {
        return lhs.year > rhs.year;
    } else if(lhs.month != rhs.month) {
        return lhs.month > rhs.month;
    }
    return lhs.day > rhs.day;
}

bool operator<=(const Date& lhs, const Date& rhs) {
//    return lhs.AsTimestamp() <= rhs.AsTimestamp();
    if(lhs.year != rhs.year) {
        return lhs.year <= rhs.year;
    } else if(lhs.month != rhs.month) {
        return lhs.month <= rhs.month;
    }
    return lhs.day <= rhs.day;
}
bool operator>=(const Date& lhs, const Date& rhs) {
//    return lhs.AsTimestamp() >= rhs.AsTimestamp();
    if(lhs.year != rhs.year) {
        return lhs.year >= rhs.year;
    } else if(lhs.month != rhs.month) {
        return lhs.month >= rhs.month;
    }
    return lhs.day >= rhs.day;
}
