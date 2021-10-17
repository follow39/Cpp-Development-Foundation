#include "budget.h"
#include <numeric>
#include <algorithm>
#include <vector>

using namespace std;

const Date START_DATE = DateFromString("2000-01-01");
const Date END_DATE = DateFromString("2100-01-01");
const int DAY_COUNT = ComputeDaysDiff(END_DATE, START_DATE);

Budget::Budget() {
    budget = vector<double>(DAY_COUNT, 0.0f);
}

void Budget::AddIncome(const Date &from, const Date &to, int value) {
    int days_count = ComputeDaysDiff(to, from) + 1;
    double incomePerDay = static_cast<double>(value) / days_count;
    auto it_from = ComputeDaysDiff(from, START_DATE);
    auto it_to = ComputeDaysDiff(to, START_DATE);
    for(auto i = it_from; i <= it_to; ++i) {
        budget[i] += incomePerDay;
    }
}

double Budget::ComputeIncome(const Date &from, const Date &to) const {
    auto it_from = budget.begin() + ComputeDaysDiff(from, START_DATE);
    auto it_to = budget.begin() + ComputeDaysDiff(to, START_DATE) + 1;
    return accumulate(it_from, it_to, 0.0f);
}
