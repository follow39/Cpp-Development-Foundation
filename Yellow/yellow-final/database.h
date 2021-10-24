#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <memory>
#include <map>
#include <set>
#include <exception>
#include <algorithm>
#include "date.h"

using Entry = std::pair<Date, std::string>;
using EntryVector = std::vector<Entry>;

class Database
{
public:
    void Add(const Date& date, const std::string& event);
    Entry Last(const Date& date) const;
    int RemoveIf(std::function<bool(const Date& date, const std::string& event)> predicate);
    EntryVector FindIf(std::function<bool(const Date& date, const std::string& event)> predicate) const;
    void Print(std::ostream& os) const;
private:
    std::map<Date, std::pair<std::vector<std::string>, std::set<std::string>>> db;
};

std::ostream& operator<<(std::ostream& os, const EntryVector& data);
std::ostream& operator<<(std::ostream& os, const Entry& data);
