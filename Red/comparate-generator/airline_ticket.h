#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <iomanip>
using namespace std;

struct Date {
  int year, month, day;
};

struct Time {
  int hours, minutes;
};

struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  int price;
};

bool operator<(const Date& lhs, const Date& rhs) {
    return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date& lhs, const Date& rhs) {
    return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

ostream& operator<<(ostream& os, const Date& date) {
    char prev = os.fill('0');
    os << setw(4) << date.year << ':' <<
          setw(2) << date.month << '-' <<
          setw(2) << date.day;
    os.fill(prev);
    return os;
}

bool operator<(const Time& lhs, const Time& rhs) {
    return tie(lhs.hours, lhs.minutes) < tie(rhs.hours, rhs.minutes);
}

bool operator==(const Time& lhs, const Time& rhs) {
    return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

ostream& operator<<(ostream& os, const Time& time) {
    char prev = os.fill('0');
    os << setw(2) << time.hours << '-' <<
          setw(2) << time.minutes;
    os.fill(prev);
    return os;
}
