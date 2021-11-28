#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include <variant>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <set>
#include <iomanip>

using namespace std;

struct Stop;
struct Bus;

struct Stop {
    string name;
    double latitude = 0.0;
    double longitude = 0.0;
    unordered_map<string, double> distance_to;

    static double CalculateGeoDistance(const Stop &first, const Stop &second) {
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
        longitude = stod(string(request.substr(0, request.find(','))));
        request.remove_prefix(request.find(',') + 2);

        while (request.find(" to ") != string_view::npos) {
//        while (!request.empty()) {
            double distance = stod(string(request.substr(0, request.find('m'))));
            request.remove_prefix(request.find("to") + 3);
            string stop_name = string(request.substr(0, request.find(',')));
            request.remove_prefix(request.find(',') + 2);

            distance_to[stop_name] = distance;
        }
    }
};

struct Bus {
    string name;
    bool isCircle = false;
    double cur_length = 0.0;
    double geo_length = 0.0;
    size_t stops_count = 0;
    size_t unique_stops_count = 0;
    vector<string> stops;

    double CalculateGeoLength(const unordered_map<string, Stop> &input_stops) {
        if (stops.empty()) {
            return 0.0;
        }
        double new_length = 0.0;
        string prev = stops[0];
        for (const auto &current: stops) {
            new_length += Stop::CalculateGeoDistance(input_stops.at(prev), input_stops.at(current));
            prev = current;
        }
        return new_length;
    }

    double CalculateCurLength(const vector<string> &stops, const unordered_map<string, Stop> &input_stops) {
        if (stops.empty()) {
            return 0.0;
        }
        double new_length = 0.0;
        string prev = stops[0];
        for (const auto &current: stops) {
            auto &prev_distance_to = input_stops.at(prev).distance_to;
            auto &current_distance_to = input_stops.at(current).distance_to;
            if (prev_distance_to.find(current) != prev_distance_to.end()) {
                new_length += prev_distance_to.at(current);
            } else if (current_distance_to.find(prev) != current_distance_to.end()) {
                new_length += current_distance_to.at(prev);
            } else {
                new_length += Stop::CalculateGeoDistance(input_stops.at(prev), input_stops.at(current));
            }
            prev = current;
        }

        return new_length;
    }

    void UpdateLength(const unordered_map<string, Stop> &input_stops) {
        geo_length = CalculateGeoLength(input_stops);
        if (!isCircle) {
            geo_length *= 2;
        }

        cur_length = CalculateCurLength(stops, input_stops);
        if (!isCircle) {
            auto temp_stops = stops;
            reverse(temp_stops.begin(), temp_stops.end());
            cur_length += CalculateCurLength(temp_stops, input_stops);
        }
    }

    Bus() = default;

    explicit Bus(string_view
                 request) {
        request.remove_prefix(4);
        name = string(request.substr(0, request.find(':')));
        request.
                remove_prefix(request
                                      .find(':') + 2);

        char splitter;
        if (request.find('-') == string_view::npos) {
            isCircle = true;
            splitter = '>';
        } else {
            isCircle = false;
            splitter = '-';
        }

        while (!request.

                empty()

                ) {
            stops.
                    emplace_back(request
                                         .substr(0, request.
                                                 find(splitter)
                                                    - 1));
            if (request.
                    find(splitter)
                == string_view::npos) {
                break;
            }
            request.
                    remove_prefix(min(request.find(splitter) + 2, request.size())
            );
        }

        stops_count = isCircle ? stops.size() : (stops.size() * 2 - 1);
//        unique_stops_count = isCircle ? ((stops.size() + 1) / 2) : stops.size();
        unordered_set<string> unique_stops(stops.begin(), stops.end());
        unique_stops_count = unique_stops.size();
    }
};

class Manager {
public:
    void AddBus(Bus new_bus) {
        for (const auto &stop: new_bus.stops) {
            buses_on_stop[stop].insert(new_bus.name);
        }

        buses[new_bus.name] = move(new_bus);
    }

    string GetBusInfo(string name) const {
        string result = "Bus " + name + ": ";
        auto it = buses.find(name);
        if (it == buses.end()) {
            result += "not found";
        } else {
            result += to_string(it->second.stops_count) + " stops on route, ";
            result += to_string(it->second.unique_stops_count) + " unique stops, ";
            result += to_string(it->second.cur_length) + " route length, ";
            result += to_string(it->second.cur_length / it->second.geo_length) + " curvature";
        }
        return result;
    }

    [[nodiscard]] string GetStopInfo(string name) const {
        string result = "Stop " + name + ": ";
        auto it = buses_on_stop.find(name);
        if (it == buses_on_stop.end()) {
            result += "not found";
        } else if (it->second.empty()) {
            result += "no buses";
        } else {
            result += "buses";
            for (const auto &bus: it->second) {
                result += " " + bus;
            }
        }
        return result;
    }

    void UpdateLengths() {
        for (auto&[name, bus]: buses) {
            bus.UpdateLength(stops);
        }
    }

    void AddStop(Stop new_stop) {
        stops[new_stop.name] = new_stop;
        buses_on_stop[new_stop.name];
    }

private:
    unordered_map<string, Bus> buses;
    unordered_map<string, Stop> stops;
    unordered_map<string, set<string>> buses_on_stop;
};

enum class CreationRequestType {
    ADD_STOP,
    ADD_BUS,
};

enum class PrintRequestType {
    PRINT_BUS,
    PRINT_STOP,
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

void ProcessCreationRequest(Manager &manager, const string &request) {
    CreationRequestType type = ParseCreationRequestType(request);
    if (type == CreationRequestType::ADD_BUS) {
        manager.AddBus(Bus(request));
    } else if (type == CreationRequestType::ADD_STOP) {
        manager.AddStop(Stop(request));
    }
}

Manager BuildManager(vector<string> requests) {
    Manager manager;
    for (auto &request: requests) {
        ProcessCreationRequest(manager, request);
    }
    manager.UpdateLengths();
    return move(manager);
}

PrintRequestType ParsePrintRequestType(const string &request) {
    PrintRequestType result;
    if (request[0] == 'S') {
        result = PrintRequestType::PRINT_STOP;
    } else {
        result = PrintRequestType::PRINT_BUS;
    }
    return result;
}

void ProcessPrintRequest(ostream &os, const Manager &manager, const string &request) {
    PrintRequestType type = ParsePrintRequestType(request);
    if (type == PrintRequestType::PRINT_BUS) {
        os << manager.GetBusInfo(string(request.substr(request.find(' ') + 1, string_view::npos))) << '\n';
    } else if (type == PrintRequestType::PRINT_STOP) {
        os << manager.GetStopInfo(string(request.substr(request.find(' ') + 1, string_view::npos))) << '\n';
    }
}

void ProcessPrintRequests(ostream &os, const Manager &manager, const vector<string> &requests) {
    for (const auto &request: requests) {
        ProcessPrintRequest(os, manager, request);
    }
}

int main() {
    cout.precision(6);

    Manager manager = BuildManager(ReadRequests(cin));
    ProcessPrintRequests(cout, manager, ReadRequests(cin));

    return 0;
}
