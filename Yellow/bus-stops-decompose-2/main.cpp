#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include "query.h"

using namespace std;


ostream& operator << (ostream& os, const vector<string>& vec) {
    bool first = true;
    for(const auto& i : vec) {
        if(!first) {
            os << ' ';
        }
        first = false;
        os << i;
    }
    return os;
}



struct BusesForStopResponse {
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if(r.buses.size() > 0) {
        os << r.buses;
    } else {
        os << "No stop";
    }
    return os;
}

struct Stop {
    string name;
    vector<string> buses;
};

struct StopsForBusResponse {
    vector<Stop> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if(r.stops.size() > 0) {
        bool first = true;
        for(const auto& i : r.stops) {
            if(!first) {
                os << '\n';
            }
            os << "Stop " << i.name << ": ";
            if(i.buses.size() > 0) {
                os << i.buses;
            } else {
                os << "no interchange";
            }
            first = false;
        }
    } else {
        os << "No bus";
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> data;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if(r.data.size() > 0) {
        for(const auto& [bus, stops] : r.data) {
            os << "Bus " << bus << ": " << stops << endl;
        }
    } else {
        os << "No buses";
    }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses[bus] = stops;
        busesInOrder.push_back(bus);
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
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

    StopsForBusResponse GetStopsForBus(const string& bus) const {
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

    AllBusesResponse GetAllBuses() const {
        return {buses};
    }
private:
    map<string, vector<string>> buses;
    vector<string> busesInOrder;
};


int main() {

    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}
