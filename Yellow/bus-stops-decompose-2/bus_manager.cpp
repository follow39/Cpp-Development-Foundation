#include "bus_manager.h"
#include <algorithm>

using namespace std;

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    buses[bus] = stops;
    busesInOrder.push_back(bus);
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    if(buses.size() == 0)
        return {};
    BusesForStopResponse result;
    for(const auto& i : busesInOrder) {
        if(count(buses.at(i).begin(), buses.at(i).end(), stop) != 0) {
            result.buses.push_back(i);
        }
    }
    return result;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    if(buses.size() == 0 || buses.count(bus) == 0)
        return {};

    StopsForBusResponse result;
    vector<string> temp;

    for(const auto& i : buses.at(bus)) {
        temp = GetBusesForStop(i).buses;
        temp.erase(find(temp.begin(), temp.end(), bus));
        result.stops.push_back({i, temp});
    }
    return result;
}

AllBusesResponse BusManager::GetAllBuses() const {
    return {buses};
}
