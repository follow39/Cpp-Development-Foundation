#ifndef QUERY_H
#define QUERY_H

#include <iostream>
#include <string>
#include <vector>

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    std::string bus;
    std::string stop;
    std::vector<std::string> stops;
};


std::istream& operator >> (std::istream& is, QueryType& q);
std::istream& operator >> (std::istream& is, std::vector<std::string>& vec);
std::istream& operator >> (std::istream& is, Query& q);

#endif // QUERY_H
