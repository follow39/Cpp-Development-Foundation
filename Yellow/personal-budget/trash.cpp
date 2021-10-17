#include <iostream>
#include <sstream>
#include <chrono>
#include <string>
#include <vector>
#include <utility>
#include <numeric>
#include <algorithm>

using namespace std;

class Date {
public:
    explicit Date(string new_date) {
        stringstream ss(new_date);
        int year = 0;
        int month = 0;
        int day = 0;
        char ch1 = 0;
        char ch2 = 0;

        ss >> year >> ch1 >> month >> ch2 >> day;

        tm t;
        t.tm_sec  = 0;
        t.tm_min  = 0;
        t.tm_hour = 0;
        t.tm_mday = day;
        t.tm_mon  = month - 1;
        t.tm_year = year - 1900;
        t.tm_isdst = 0;

        date = mktime(&t);
    }

    time_t GetDate() const {
        return date;
    }

private:
    time_t date;
};

int ComputeDaysDiff(const Date& date_to, const Date& date_from) {
    const time_t timestamp_to = date_to.GetDate();
    const time_t timestamp_from = date_from.GetDate();
    static constexpr int SECONDS_IN_DAY = 60 * 60 * 24;
    return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

const Date START_DATE{"2000-01-01"};
const Date END_DATE{"2100-01-01"};
const int DAY_COUNT = ComputeDaysDiff(END_DATE, START_DATE);

class Budget
{
public:
    Budget() {
        budget = vector<double>(DAY_COUNT, 0.0f);
    }

    void AddIncome(const Date& from, const Date& to, int value) {
        int days_count = ComputeDaysDiff(to, from) + 1;
        double incomePerDay = static_cast<double>(value) / days_count;
        auto it_from = ComputeDaysDiff(from, START_DATE);
        auto it_to = ComputeDaysDiff(to, START_DATE);
        for(auto i = it_from; i <= it_to; ++i) {
            budget[i] += incomePerDay;
        }
    }
    double ComputeIncome(const Date& from, const Date& to) const {
        auto it_from = budget.begin() + ComputeDaysDiff(from, START_DATE);
        auto it_to = budget.begin() + ComputeDaysDiff(to, START_DATE) + 1;
        return accumulate(it_from, it_to, 0.);
    }
private:
    std::vector<double> budget;
};

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
            cout << fixed << budget.ComputeIncome(Date{from}, Date{to}) << endl;
        }
        if(cmd == "Earn") {
            int value = 0;
            cin >> from >> to >> value;
            budget.AddIncome(Date{from}, Date{to}, value);
        }
    }
    return 0;
}
