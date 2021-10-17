#include <iostream>
#include <vector>
#include <utility>
#include <chrono>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;

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
    void operator--();
private:
    int year;
    int month;
    int day;
};

int GetDaysCount(int year, int month);
time_t AsTimestamp(const Date& date);
int ComputeDaysDiff(const Date& date_to, const Date& date_from);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
int operator-(const Date& lhs, const Date& rhs);

struct DayBudget {
    Date date;
    double value = 0;
};

class Budget
{
public:
    Budget();

    void AddIncome(const Date& from, const Date& to, int value);
    double ComputeIncome(const Date& from, const Date& to) const;
private:
    std::vector<DayBudget> budget;
};

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

void Date::operator--() {
    --day;
    if(day == 0) {
        --month;
        if(month == 0) {
            month = 12;
            --year;
        }
        day = GetDaysCount(year, month);
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
    vector<DayBudget> vec;
    int days_count = ComputeDaysDiff(to, from) + 1;
    double incomePerDay = static_cast<double>(value) / days_count;
    for(Date it = from; it <= to; ++it) {
        auto it_find = find_if(budget.begin(), budget.end(), [it](const DayBudget& db) {
            return it == db.date;
        });
        if(it_find != budget.end())
        {
            it_find->value += incomePerDay;
        } else {
            vec.push_back({it, incomePerDay});
        }
    }
    budget.insert(budget.end(), vec.begin(), vec.end());
    sort(budget.begin(), budget.end(), [](const DayBudget& lhs, const DayBudget& rhs) { return lhs.date < rhs.date; });
}

double Budget::ComputeIncome(const Date &from, const Date &to) const {
    const auto& it1 = find_if(budget.begin(), budget.end(), [from](const auto& i) {
        return i.date >= from;
    });
    const auto& it2 = find_if(budget.begin(), budget.end(), [to](const auto& i) {
        return i.date > to;
    });
    return accumulate(it1, it2, 0.0f, [](double res, const auto& i) {
        return res + i.value;
    });
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
