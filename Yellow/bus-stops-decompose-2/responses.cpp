#include "responses.h"

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

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if(r.buses.size() > 0) {
        os << r.buses;
    } else {
        os << "No stop";
    }
    return os;
}

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
