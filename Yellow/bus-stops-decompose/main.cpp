#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

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

//ostream& operator << (ostream& os, const map<string, vector<string>>& m) {
//    for(const auto& [key, value] : m) {
//        os << "Bus " << key << ": " << value << endl;
//    }
//    return os;
//}

istream& operator >> (istream& is, Query& q) {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
    int temp;

    is >> type;
    switch (type) {
    case QueryType::NewBus:
        is >> bus >> temp >>stops;
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
        BusesForStopResponse result;
        for(const auto& i : busesInOrder) {
            if(count(buses.at(i).begin(), buses.at(i).end(), stop) != 0) {
                result.buses.push_back(i);
            }
        }
        return result;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        if(buses.size() == 0)
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
