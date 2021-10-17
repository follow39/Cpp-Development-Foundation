#include "budget.h"
#include <numeric>
#include <algorithm>
#include <vector>

using namespace std;

Budget::Budget() {
}

void Budget::AddIncome(const Date &from, const Date &to, int value) {
    Date it = from;
    double days_count = 0;
    while(it <= to) {
        ++days_count;
        ++it;
    }

    it = from;
    double incomePerDay = value / days_count;
    while(it <= to) {
        budget[it] += incomePerDay;
        ++it;
    }
}

int foo(pair<Date, int> p, int res);

int Budget::ComputeIncome(const Date &from, const Date &to) const {
    const auto& it1 = find_if(budget.begin(), budget.end(), [from](const std::map<Date, int>::value_type& i) {
        return i.first >= from;
    });
    const auto& it2 = find_if(budget.rbegin(), budget.rend(), [to](const std::map<Date, int>::value_type& i) {
        return i.first <= to;
    });

    return accumulate(it1, it2.base(), 0, [](int res, const std::map<Date, int>::value_type& i) {
        return res + i.second;
    });
    //    return accumulate(budget.begin(), budget.end(), 0,
    //                      [](int res, const std::map<Date, int>::value_type& i) {
    //                            return res + i.second;
    //                        });
}
