#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <numeric>
#include <algorithm>
#include <iomanip>

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
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
int operator-(const Date& lhs, const Date& rhs);

class Budget
{
public:
    Budget();

    void AddIncome(const Date& from, const Date& to, int value);
    double ComputeIncome(const Date& from, const Date& to) const;
private:
    std::map<Date, double> budget;
};

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

Budget::Budget() {
}

void Budget::AddIncome(const Date &from, const Date &to, int value) {
    Date it = from;
    int days_count = 0;
    while(it <= to) {
        ++days_count;
        ++it;
    }
    it = from;
    double incomePerDay = static_cast<double>(value) / days_count;
    while(it <= to) {
        budget[it] += incomePerDay;
        ++it;
    }
}

double Budget::ComputeIncome(const Date &from, const Date &to) const {
    const auto& it1 = find_if(budget.begin(), budget.end(), [from](const std::map<Date, int>::value_type& i) {
        return i.first >= from;
    });
    const auto& it2 = find_if(budget.rbegin(), budget.rend(), [to](const std::map<Date, int>::value_type& i) {
        return i.first <= to;
    });
    return accumulate(it1, it2.base(), 0.0, [](double res, const std::map<Date, double>::value_type& i) {
        return res + i.second;
    });
}

int main()
{
    Budget budget;
    string cmd;
    string from;
    string to;

    int q = 0;
    cin >> q;
    cout.precision(25);
    while(q-- > 0) {
        cin >> cmd;
        if(cmd == "ComputeIncome") {
            cin >> from >> to;
            cout << fixed << budget.ComputeIncome(DateFromString(from), DateFromString(to)) << endl;
        }
        if(cmd == "Earn") {
            int value = 0;
            cin >> from >> to >> value;
            budget.AddIncome(DateFromString(from), DateFromString(to), value);
        }
    }

    return 0;
}
