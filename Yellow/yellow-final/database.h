#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <utility>
#include <memory>
#include "date.h"

using DBaseUnit = std::pair<Date, std::string>;
using DBase = std::vector<DBaseUnit>;

class Database
{
public:
    void Add(const Date& date, const std::string& event);
    DBaseUnit Last(const Date& date) const;
    int RemoveIf(std::function<bool(const Date& date, const std::string& event)> predicate);
    DBase FindIf(std::function<bool(const Date& date, const std::string& event)> predicate);
    void Print(std::ostream& os) const;
private:
    DBase db;
};

std::ostream& operator<<(std::ostream& os, const DBase& data);
std::ostream& operator<<(std::ostream& os, const DBaseUnit& data);
