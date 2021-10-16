#include "budget.h"
#include <numeric>
#include <algorithm>

using namespace std;

Budget::Budget() {
}

void Budget::AddIncome(const Date &from, const Date &to, int value) {

}

int Budget::ComputeIncome(const Date &from, const Date &to) const {
    return accumulate(budget.at(from), budget.at(to), 0);
}
