#pragma once

#include <iostream>
#include <string>
#include <map>
#include <set>
#include "date.h"

class Database
{
public:
    void AddEvent(const Date& date, const std::string& event);
    bool DeleteEvent(const Date& date, const std::string& event);
    int  DeleteDate(const Date& date);
    std::set<std::string> Find(const Date& date) const;
    std::ostream& Print(std::ostream& os) const;
private:
    std::map<Date, std::set<std::string>> db;
};

std::ostream& operator<<(std::ostream& os, std::set<std::string> data);
