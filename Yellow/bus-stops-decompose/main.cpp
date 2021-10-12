#include <iostream>
#include <string>
#include <map>
#include <vector>

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

istream& operator >> (istream& is, Query& q) {
    // п═п╣п╟п╩п╦п╥я┐п╧я┌п╣ я█я┌я┐ я└я┐п╫п╨я├п╦я▌
    return is;
}

struct BusesForStopResponse {
    // п²п╟п©п╬п╩п╫п╦я┌п╣ п©п╬п╩я▐п╪п╦ я█я┌я┐ я│я┌я─я┐п╨я┌я┐я─я┐
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    // п═п╣п╟п╩п╦п╥я┐п╧я┌п╣ я█я┌я┐ я└я┐п╫п╨я├п╦я▌
    return os;
}

struct StopsForBusResponse {
    // п²п╟п©п╬п╩п╫п╦я┌п╣ п©п╬п╩я▐п╪п╦ я█я┌я┐ я│я┌я─я┐п╨я┌я┐я─я┐
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    // п═п╣п╟п╩п╦п╥я┐п╧я┌п╣ я█я┌я┐ я└я┐п╫п╨я├п╦я▌
    return os;
}

struct AllBusesResponse {
    // п²п╟п©п╬п╩п╫п╦я┌п╣ п©п╬п╩я▐п╪п╦ я█я┌я┐ я│я┌я─я┐п╨я┌я┐я─я┐
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    // п═п╣п╟п╩п╦п╥я┐п╧я┌п╣ я█я┌я┐ я└я┐п╫п╨я├п╦я▌
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        // п═п╣п╟п╩п╦п╥я┐п╧я┌п╣ я█я┌п╬я┌ п╪п╣я┌п╬п╢
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // п═п╣п╟п╩п╦п╥я┐п╧я┌п╣ я█я┌п╬я┌ п╪п╣я┌п╬п╢
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        // п═п╣п╟п╩п╦п╥я┐п╧я┌п╣ я█я┌п╬я┌ п╪п╣я┌п╬п╢
    }

    AllBusesResponse GetAllBuses() const {
        // п═п╣п╟п╩п╦п╥я┐п╧я┌п╣ я█я┌п╬я┌ п╪п╣я┌п╬п╢
    }
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





    int q;
    cin >> q;

    map<string, vector<string>> buses_to_stops, stops_to_buses;

    for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "NEW_BUS") {

            string bus;
            cin >> bus;
            int stop_count;
            cin >> stop_count;
            vector<string>& stops = buses_to_stops[bus];
            stops.resize(stop_count);
            for (string& stop : stops) {
                cin >> stop;
                stops_to_buses[stop].push_back(bus);
            }

        } else if (operation_code == "BUSES_FOR_STOP") {

            string stop;
            cin >> stop;
            if (stops_to_buses.count(stop) == 0) {
                cout << "No stop" << endl;
            } else {
                for (const string& bus : stops_to_buses[stop]) {
                    cout << bus << " ";
                }
                cout << endl;
            }

        } else if (operation_code == "STOPS_FOR_BUS") {

            string bus;
            cin >> bus;
            if (buses_to_stops.count(bus) == 0) {
                cout << "No bus" << endl;
            } else {
                for (const string& stop : buses_to_stops[bus]) {
                    cout << "Stop " << stop << ": ";
                    if (stops_to_buses[stop].size() == 1) {
                        cout << "no interchange";
                    } else {
                        for (const string& other_bus : stops_to_buses[stop]) {
                            if (bus != other_bus) {
                                cout << other_bus << " ";
                            }
                        }
                    }
                    cout << endl;
                }
            }

        } else if (operation_code == "ALL_BUSES") {

            if (buses_to_stops.empty()) {
                cout << "No buses" << endl;
            } else {
                for (const auto& bus_item : buses_to_stops) {
                    cout << "Bus " << bus_item.first << ": ";
                    for (const string& stop : bus_item.second) {
                        cout << stop << " ";
                    }
                    cout << endl;
                }
            }

        }
    }

    return 0;
}