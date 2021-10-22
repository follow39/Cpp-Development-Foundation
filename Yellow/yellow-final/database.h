#pragma once

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <functional>
#include "date.h"

using events = std::set<std::string>;
using dBase = std::map<Date, events>;

class Database
{
public:
    void Add(const Date& date, const std::string& event);
    std::pair<Date, events> Last(const Date& date);
    bool DeleteEvent(const Date& date, const std::string& event);
    int  DeleteDate(const Date& date);
    int RemoveIf(std::function<bool(const Date& date, const std::string& event)> predicate);
    dBase FindIf(std::function<bool(const Date& date, const std::string& event)> predicate);
    events Find(const Date& date) const;
    std::ostream& Print(std::ostream& os) const;
private:
    dBase db;
};

std::ostream& operator<<(std::ostream& os, dBase data);
std::ostream& operator<<(std::ostream& os, std::pair<Date, std::set<std::string>> data);
std::ostream& operator<<(std::ostream& os, events data);
