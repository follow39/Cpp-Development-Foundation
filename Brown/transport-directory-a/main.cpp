#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include <variant>
#include <optional>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <memory>
#include <iomanip>

using namespace std;


struct Stop {
    string name;
    double latitude = 0.0;
    double longitude = 0.0;

    static double CalculateDistance(const Stop &first, const Stop &second) {
//        return sqrt(pow((first.latitude - second.latitude), 2) +
//                    pow((first.longitude - second.latitude), 2));

        auto hav = [](double value) { return (1 - cos(value * M_PI / 180)) / 2; };
        const double r = 6'371'000;

        return 2 * r * asin(sqrt(hav(second.latitude - first.latitude) +
                                 (1 - hav(first.latitude - second.latitude) -
                                  hav(first.latitude + second.latitude)) *
                                 hav(second.longitude - first.longitude)));
    }

    Stop() = default;

    explicit Stop(string_view request) {
        request.remove_prefix(5);
        name = string(request.substr(0, request.find(':')));
        request.remove_prefix(request.find(':') + 2);
        latitude = stod(string(request.substr(0, request.find(','))));
        request.remove_prefix(request.find(',') + 2);
        longitude = stod(string(request.substr()));
    }
};

struct BusName {
    string value;
};

class StopManager {
public:
    void AddStop(Stop new_stop) {
        stops[new_stop.name] = new_stop;
    }

    [[nodiscard]] const unordered_map<string, Stop> &GetStops() const {
        return stops;
    }

    [[nodiscard]] const Stop &At(string name) const {
        return stops.at(name);
    }

private:
    unordered_map<string, Stop> stops;
};

struct Bus {
    string name;
    bool isCircle = false;
    double length = 0.0;
    size_t stops_count = 0;
    size_t unique_stops_count = 0;
    vector<string> stops;

    double CalculateLength(const StopManager &stopManager) {
        if (stops.empty()) {
            return 0;
        }
        double new_length = 0.0;
        string prev = stops[0];

        for (const auto &current: stops) {
            new_length += Stop::CalculateDistance(stopManager.At(prev), stopManager.At(current));
            prev = current;
        }

        return new_length;
    }

    void UpdateLength(const StopManager &stopManager) {
        length = CalculateLength(stopManager);
        if (!isCircle) {
            length *= 2;
        }
    }

    Bus() = default;

    explicit Bus(string_view request) {
        request.remove_prefix(4);
        name = string(request.substr(0, request.find(':')));
        request.remove_prefix(request.find(':') + 2);

        char splitter;
        if (request.find('-') == string_view::npos) {
            isCircle = true;
            splitter = '>';
        } else {
            isCircle = false;
            splitter = '-';
        }

        while (!request.empty()) {
            stops.emplace_back(request.substr(0, request.find(splitter) - 1));
            if (request.find(splitter) == string_view::npos) {
                break;
            }
            request.remove_prefix(min(request.find(splitter) + 2, request.size()));
        }

        stops_count = isCircle ? stops.size() : (stops.size() * 2 - 1);
//        unique_stops_count = isCircle ? ((stops.size() + 1) / 2) : stops.size();
        unordered_set<string> unique_stops(stops.begin(), stops.end());
        unique_stops_count = unique_stops.size();
    }
};

class BusManager {
public:
    void AddBus(Bus new_bus) {
        buses[new_bus.name] = move(new_bus);
    }

    [[nodiscard]] const Bus &GetBus(string name) const {
        return buses.at(name);
    }

    string GetBusInfo(string name) const {
        string result = "Bus " + name + ": ";
        auto it = buses.find(name);
        if (it == buses.end()) {
            result += "not found";
        } else {
            result += to_string(it->second.stops_count) + " stops on route, ";
            result += to_string(it->second.unique_stops_count) + " unique stops, ";
            result += to_string(it->second.length) + " route length";
        }
        return result;
    }

    void UpdateLenghts(const StopManager &stopManager) {
        for (auto&[name, bus]: buses) {
            bus.UpdateLength(stopManager);
        }
    }

private:
    unordered_map<string, Bus> buses;
};

enum class CreationRequestType {
    ADD_STOP,
    ADD_BUS,
};

enum class PrintRequestType {
    PRINT_BUS,
};

struct BuildManagersStruct {
    StopManager stopManager;
    BusManager busManager;
};

vector<string> ReadRequests(istream &is) {
    size_t n = 0;
    is >> n;
    is.ignore(1);

    vector<string> result;
//    string line;
//    while (getline(is, line)) {
//        if (!line.empty()) {
//            result.push_back(line);
//        }
//    }
    while (n-- > 0) {
        string line;
        getline(is, line);
        result.push_back(line);
    }
//    is >> n;
//    is.ignore(1);
//    while (n-- > 0) {
//        string line;
//        getline(is, line);
//        result.push_back(line);
//    }
    return move(result);
}

CreationRequestType ParseCreationRequestType(const string &request) {
    CreationRequestType result;
    if (request[0] == 'S') {
        result = CreationRequestType::ADD_STOP;
    } else {
        result = CreationRequestType::ADD_BUS;
    }
    return result;
}

void ProcessCreationRequest(BuildManagersStruct &managers, const string &request) {
    CreationRequestType type = ParseCreationRequestType(request);
    if (type == CreationRequestType::ADD_BUS) {
        managers.busManager.AddBus(Bus(request));
    } else if (type == CreationRequestType::ADD_STOP) {
        managers.stopManager.AddStop(Stop(request));
    }
}

BuildManagersStruct BuildManagers(vector<string> requests) {
    BuildManagersStruct managers;

    for (auto &request: requests) {
        ProcessCreationRequest(managers, request);
    }

    managers.busManager.UpdateLenghts(managers.stopManager);

    return move(managers);
}

void ProcessPrintRequest(ostream &os, const BusManager &busManager, string_view request) {
    os << busManager.GetBusInfo(string(request.substr(4, string_view::npos))) << '\n';
}

void ProcessPrintRequests(ostream &os, const BusManager &busManager, const vector<string> &requests) {
    for (const auto &request: requests) {
        ProcessPrintRequest(os, busManager, request);
    }
}

int main() {
    cout.precision(6);

    auto[stopManager, busManager] = BuildManagers(ReadRequests(cin));
    ProcessPrintRequests(cout, busManager, ReadRequests(cin));

    return 0;
}
