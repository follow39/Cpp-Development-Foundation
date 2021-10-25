#include "airline_ticket.h"
#include "test_runner.h"
#include <iostream>
#include <iomanip>

using namespace std;

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

istream& operator>>(istream& is, Date& date) {
    int year = 0;
    int month = 0;
    int day = 0;
    char ch1 = 0;
    char ch2 = 0;
    is >> year >> ch1 >> month >> ch2 >> day;
    date.year = year;
    date.month = month;
    date.day = day;
    return is;
}

bool operator<(const Time& lhs, const Time& rhs) {
    return tie(lhs.hours, lhs.minutes) < tie(rhs.hours, rhs.minutes);
}

bool operator==(const Time& lhs, const Time& rhs) {
    return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

ostream& operator<<(ostream& os, const Time& time) {
    char prev = os.fill('0');
    os << setw(2) << time.hours << ':' <<
          setw(2) << time.minutes;
    os.fill(prev);
    return os;
}

istream& operator>>(istream& is, Time& time) {
    int hours = 0;
    int minutes = 0;
    char ch1 = 0;
    is >> hours >> ch1 >> minutes;
    time.hours = hours;
    time.minutes = minutes;
    return is;
}

#define UPDATE_FIELD(ticket, field, values) {       \
    auto it = values.find(#field);                  \
    if(it != values.end()) {                        \
        istringstream is(it->second);               \
        is >> ticket.field;                         \
    }                                               \
}

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
