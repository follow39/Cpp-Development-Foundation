#include "budget.h"
#include <numeric>
#include <algorithm>
#include <vector>

using namespace std;

Budget::Budget() {
}

void Budget::AddIncome(const Date &from, const Date &to, int value) {
    Date it = from;
    Date it_from = from;
    Date it_to = to;
    ++it_to;
    int days_count = ComputeDaysDiff(it_to, it_from);
    double incomePerDay = static_cast<double>(value) / days_count;
    while(it <= to) {
        budget.push_back({it, incomePerDay});
        ++it;
    }
}

double Budget::ComputeIncome(const Date &from, const Date &to) const {
    const auto& it1 = find_if(budget.begin(), budget.end(), [from](const auto& i) {
        return i.date >= from;
    });
    const auto& it2 = find_if(budget.rbegin(), budget.rend(), [to](const auto& i) {
        return i.date <= to;
    });
    return accumulate(it1, it2.base(), 0.0f, [](double res, const auto& i) {
        return res + i.value;
    });
}
