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

long long ComputeDaysDiff(const Date& date_to, const Date& date_from) {
    const time_t timestamp_to = date_to.GetDate();
    const time_t timestamp_from = date_from.GetDate();
    static constexpr int SECONDS_IN_DAY = 60 * 60 * 24;
    return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

static const Date START_DATE{"1700-01-01"};
static const Date END_DATE{"2100-01-01"};
const long long DAY_COUNT = ComputeDaysDiff(END_DATE, START_DATE);

class Budget
{
public:
    Budget() {
        budget = vector<long long>(DAY_COUNT, 0);
        budget_sum = vector<long long>(DAY_COUNT, 0);
    }

    void AddIncome(const Date& date, long long value) {
        budget[ComputeDaysDiff(date, START_DATE)] += value;
    }
    long long ComputeIncome(const Date& from, const Date& to) const {
        auto it_from = ComputeDaysDiff(from, START_DATE);
        auto it_to = ComputeDaysDiff(to, START_DATE);
        return budget_sum[it_to] - budget_sum[it_from] + budget[it_from];
    }
    void GeneratePartialSum() {
        partial_sum(budget.begin() , budget.end(), budget_sum.begin());
    }
private:
    std::vector<long long> budget;
    std::vector<long long> budget_sum;
};

int main()
{
    Budget budget;
    string date;
    long long value = 0;
    string from;
    string to;

    int q = 0;
    cin >> q;
    while(q-- > 0) {
        cin >> date >> value;
        budget.AddIncome(Date{date}, value);
    }
    budget.GeneratePartialSum();
    cin >> q;
    while(q-- > 0) {
        cin >> from >> to;
        cout << budget.ComputeIncome(Date{from}, Date{to}) << endl;
    }
    return 0;
}
