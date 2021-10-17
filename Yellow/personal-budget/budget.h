#ifndef BUDGET_H
#define BUDGET_H

#include <vector>
#include <utility>
#include "date.h"



class Budget
{
public:
    Budget();

    void AddIncome(const Date& from, const Date& to, int value);
    double ComputeIncome(const Date& from, const Date& to) const;
private:
    std::vector<double> budget;
};

#endif // BUDGET_H
