#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <memory>
#include <map>
#include <set>
#include "date.h"

using DBaseUnit = std::pair<Date, std::string>;
using Entry = DBaseUnit;
using DBase = std::vector<DBaseUnit>;

class Database
{
public:
    void Add(const Date& date, const std::string& event);
    DBaseUnit Last(const Date& date) const;
    int RemoveIf(std::function<bool(const Date& date, const std::string& event)> predicate);
    DBase FindIf(std::function<bool(const Date& date, const std::string& event)> predicate) const;
    void Print(std::ostream& os) const;
private:
    std::map<Date, std::vector<std::string>> db_vector;
    std::map<Date, std::set<std::string>> db_set;
    std::map<Date, std::pair<std::vector<std::string>, std::set<std::string>>> db;
};

std::ostream& operator<<(std::ostream& os, const DBase& data);
std::ostream& operator<<(std::ostream& os, const DBaseUnit& data);
