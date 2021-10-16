#ifndef RESPONSES_H
#define RESPONSES_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

struct BusesForStopResponse {
    std::vector<std::string> buses;
};

struct Stop {
    std::string name;
    std::vector<std::string> buses;
};

struct StopsForBusResponse {
    std::vector<Stop> stops;
};


struct AllBusesResponse {
    std::map<std::string, std::vector<std::string>> data;
};

std::ostream& operator << (std::ostream& os, const std::vector<std::string>& vec);
std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);
std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);
std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);

#endif // RESPONSES_H
