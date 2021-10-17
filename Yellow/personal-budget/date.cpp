#include "date.h"
#include <sstream>

using namespace std;

Date::Date(int new_year, int new_month, int new_day) {
    year = new_year;
    month = new_month;
    day = new_day;
}

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
