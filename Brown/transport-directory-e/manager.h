#pragma once

#include "stop.h"
#include "bus.h"
#include "json.h"

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <optional>

class Manager {
public:
    void AddBus(Bus new_bus) {
        for (const auto &stop: new_bus.stops) {
            buses_on_stop[stop].insert(new_bus.name);
        }

        buses[new_bus.name] = std::move(new_bus);
    }

    [[nodiscard]] std::optional<BusInfo> GetBusInfo(const std::string &name) const {
        std::optional < BusInfo > result;
        auto it = buses.find(name);
        if (it != buses.end()) {
            result = it->second.GetBusInfo();
        }
        return result;
    }

    [[nodiscard]] std::optional<StopInfo> GetStopInfo(const std::string &name) const {
        std::optional < StopInfo > result;
        auto it = buses_on_stop.find(name);
        if (it != buses_on_stop.end()) {
            result = {.buses = it->second};
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