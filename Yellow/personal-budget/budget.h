#ifndef BUDGET_H
#define BUDGET_H

#include <map>
#include "date.h"


class Budget
{
public:
    Budget();

    void AddIncome(const Date& from, const Date& to, int value);
    int ComputeIncome(const Date& from, const Date& to) const;
private:
    std::map<Date, double> budget;
};

#endif // BUDGET_H
