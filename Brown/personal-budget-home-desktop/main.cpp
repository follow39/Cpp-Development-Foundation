#include <iostream>
#include <sstream>
#include <chrono>
#include <string>
#include <vector>
#include <utility>
#include <iomanip>
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
        t.tm_sec = 0;
        t.tm_min = 0;
        t.tm_hour = 0;
        t.tm_mday = day;
        t.tm_mon = month - 1;
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

int64_t ComputeDaysDiff(const Date &date_to, const Date &date_from) {
    const time_t timestamp_to = date_to.GetDate();
    const time_t timestamp_from = date_from.GetDate();
    static constexpr int SECONDS_IN_DAY = 60 * 60 * 24;
    return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

static const Date START_DATE{"2000-01-01"};
static const Date END_DATE{"2100-01-01"};
const int64_t DAY_COUNT = ComputeDaysDiff(END_DATE, START_DATE);

class Budget {
public:
    Budget() : budget(DAY_COUNT, 0) {}

    void AddIncome(const Date &from, const Date &to, double value) {
        double days_count = static_cast<double>(ComputeDaysDiff(to, from) + 1);
        ChangeBudget(from, to, [&](int64_t i) { budget[i] += value / days_count; });
    }

    double ComputeIncome(const Date &from, const Date &to) const {
        double result = 0;
        ChangeBudget(from, to, [&](int64_t i) { result += budget[i]; });
        return result;
    }

    void PayTax(const Date &from, const Date &to, double value) {
        ChangeBudget(from, to, [&](int64_t i) { budget[i] *= (1 - value); });
    }


private:
    template<typename Predicate>
    void ChangeBudget(const Date &from, const Date &to, Predicate predicate) const {
        auto it_from = ComputeDaysDiff(from, START_DATE);
        auto it_to = ComputeDaysDiff(to, START_DATE);
        for (auto i = it_from; i <= it_to && i < budget.size(); ++i) {
            predicate(i);
        }
    }

    std::vector<double> budget;
};

int main() {
    cout.precision(25);

    Budget budget;

    int q = 0;
    cin >> q;
    while (q-- > 0) {
        string cmd, from, to;
        cin >> cmd >> from >> to;

        if (cmd == "Earn") {
            int64_t value = 0;
            cin >> value;
            budget.AddIncome(Date{from}, Date{to}, value);
        } else if (cmd == "ComputeIncome") {
            cout << budget.ComputeIncome(Date{from}, Date{to}) << '\n';
        } else if (cmd == "PayTax") {
            budget.PayTax(Date{from}, Date{to}, 0.13);
        }
    }
    return 0;
}
