#pragma once

#include "stop.h"
#include "bus.h"

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <algorithm>

class Manager {
public:
    void AddBus(Bus new_bus) {
        for (const auto &stop: new_bus.stops) {
            buses_on_stop[stop].insert(new_bus.name);
        }

        buses[new_bus.name] = std::move(new_bus);
    }

    [[nodiscard]] std::string GetBusInfo(const std::string &name) const {
        std::string result = "Bus " + name + ": ";
        auto it = buses.find(name);
        if (it == buses.end()) {
            result += "not found";
        } else {
            result += std::to_string(it->second.stops_count) + " stops on route, ";
            result += std::to_string(it->second.unique_stops_count) + " unique stops, ";
            result += std::to_string(it->second.cur_length) + " route length, ";
            result += std::to_string(it->second.cur_length / it->second.geo_length) + " curvature";
        }
        return result;
    }

    [[nodiscard]] std::string GetStopInfo(const std::string &name) const {
        std::string result = "Stop " + name + ": ";
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
        buses_on_stop[new_stop.name];
        stops[new_stop.name] = std::move(new_stop);
    }

private:
    std::unordered_map<std::string, Bus> buses;
    std::unordered_map<std::string, Stop> stops;
    std::unordered_map<std::string, std::set<std::string>> buses_on_stop;
};