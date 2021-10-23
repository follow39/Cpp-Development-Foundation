#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <utility>
#include <memory>
#include "date.h"

using Events = std::vector<std::string>;
using DBaseUnit = std::pair<Date, Events>;
using DBase = std::vector<std::shared_ptr<DBaseUnit>>;

class Database
{
public:
    void Add(const Date& date, const std::string& event);
    std::pair<Date, Events> Last(const Date& date) const;
//    int RemoveIf(std::function<bool(const Date& date, const std::string& event)> predicate);
//    DBase FindIf(std::function<bool(const Date& date, const std::string& event)> predicate);
    void Print(std::ostream& os) const;
private:
    DBase db;
};

std::ostream& operator<<(std::ostream& os, const DBase& data);
std::ostream& operator<<(std::ostream& os, const DBaseUnit& data);
