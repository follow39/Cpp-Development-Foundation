#pragma once

#include "stop.h"
#include "bus.h"
#include "json.h"
#include "graph.h"
#include "router.h"
#include "path.h"

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
        std::optional<BusInfo> result;
        auto it = buses.find(name);
        if (it != buses.end()) {
            result = it->second.GetBusInfo();
        }
        return result;
    }

    [[nodiscard]] std::optional<StopInfo> GetStopInfo(const std::string &name) const {
        std::optional<StopInfo> result;
        auto it = buses_on_stop.find(name);
        if (it != buses_on_stop.end()) {
            result = {.buses = it->second};
        }
        return result;
    }

    void UpdateLengths() {
        for (auto&[main_name, main_stop]: stops) {
            for (auto&[second_name, length]: main_stop.distance_to) {
                if (stops.at(second_name).distance_to.count(main_name) == 0) {
                    stops.at(second_name).distance_to.emplace(main_name, length);
                }
            }
        }
        for (auto&[name, bus]: buses) {
            bus.UpdateLength(stops);
        }
    }

    void AddStop(Stop new_stop) {
        stopsIndex.push_back(new_stop.name);
        stopsInvertedIndex.emplace(new_stop.name, stopsIndex.size() - 1);
        buses_on_stop[new_stop.name];
        stops[new_stop.name] = std::move(new_stop);
    }

    void SetRoutingSettings(const RoutingSettings& new_routingSettings) {
        routingSettings = new_routingSettings;
    }

    [[nodiscard]] Graph::DirectedWeightedGraph<double> BuildGraph() const {
        Graph::DirectedWeightedGraph<double> graph(stops.size());
        return graph;
    }

    [[nodiscard]] std::optional<Path> GetPath(const PathRequest& pathRequest) const {
        return std::nullopt;
    }

private:
    RoutingSettings routingSettings;
    std::unordered_map<std::string, Bus> buses;
    std::unordered_map<std::string, Stop> stops;
    std::unordered_map<std::string, std::set<std::string>> buses_on_stop;

    std::vector<std::string> stopsIndex;
    std::unordered_map<std::string, Graph::VertexId> stopsInvertedIndex;
};