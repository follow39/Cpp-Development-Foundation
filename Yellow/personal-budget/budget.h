#ifndef BUDGET_H
#define BUDGET_H

#include <vector>
#include <utility>
#include "date.h"

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

#endif // BUDGET_H
