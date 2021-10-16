#include "query.h"
#include <sstream>

using namespace std;

istream& operator >> (istream& is, QueryType& q) {
    string cmd;
    is >> cmd;
    if(cmd == "NEW_BUS") {
        q = QueryType::NewBus;
    } else if(cmd == "BUSES_FOR_STOP") {
        q = QueryType::BusesForStop;
    } else if(cmd == "STOPS_FOR_BUS") {
        q = QueryType::StopsForBus;
    } else if(cmd == "ALL_BUSES") {
        q = QueryType::AllBuses;
    }
    return is;
}

istream& operator >> (istream& is, vector<string>& vec) {
    string temp;
    getline(is, temp);
    stringstream ss(temp);
    while(ss >> temp) {
        vec.push_back(temp);
    }
    return is;
}

istream& operator >> (istream& is, Query& q) {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
    int temp;

    is >> type;
    switch (type) {
    case QueryType::NewBus:
        is >> bus >> temp >> stops;
        break;
    case QueryType::BusesForStop:
        is >> stop;
        break;
    case QueryType::StopsForBus:
        is >> bus;
        break;
    case QueryType::AllBuses:
        break;
    }
    q = {type, bus, stop, stops};

    return is;
}
