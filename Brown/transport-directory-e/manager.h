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
#include <memory>
#include <algorithm>

class Manager {
public:
    struct WaitEdge {
        std::string stop_name;
        double time = 0.0;
    };

    struct BusEdge {
        std::string bus_name;
        std::string from;
        std::string to;
        int span_count = 0;
        double time = 0;
    };

    Manager() = default;

    explicit Manager(RoutingSettings new_routingSettings) : routingSettings(new_routingSettings) {}

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

    void PrepareToProcess() {
        UpdateLengths();
        CreateRouter();
    }

    void AddStop(Stop new_stop) {
        indexStops.push_back(new_stop.name);
        indexStops.push_back(new_stop.name);
        invertedIndexStops.emplace(new_stop.name, indexStops.size() - 2);
        buses_on_stop[new_stop.name];
        stops[new_stop.name] = std::move(new_stop);
    }

    [[nodiscard]] std::optional<PathResponse> RoutePath(const PathRequest &pathRequest) const {
        if (!router) {
            return std::nullopt;
        }
        if (invertedIndexStops.find(pathRequest.from) == invertedIndexStops.end() ||
            invertedIndexStops.find(pathRequest.to) == invertedIndexStops.end()) {
            return std::nullopt;
        }
        auto route = router->BuildRoute(invertedIndexStops.at(pathRequest.from),
                                        invertedIndexStops.at(pathRequest.to));
        if (!route) {
            return std::nullopt;
        }
        PathResponse result;
        for (size_t i = 0; i < route->edge_count; ++i) {
            auto edge = edges[router->GetRouteEdge(route->id, i)];

            if (std::holds_alternative<WaitEdge>(edge)) {
                WaitResponseItem waitResponseItem{};
                waitResponseItem.stop_name = std::get<WaitEdge>(edge).stop_name;
                waitResponseItem.time = std::get<WaitEdge>(edge).time;
                result.items.emplace_back(std::make_unique<WaitResponseItem>(std::move(waitResponseItem)));
            } else if (std::holds_alternative<BusEdge>(edge)) {
                BusResponseItem busResponseItem{};
                busResponseItem.bus_name = std::get<BusEdge>(edge).bus_name;
                busResponseItem.span_count = std::get<BusEdge>(edge).span_count;
                busResponseItem.time = std::get<BusEdge>(edge).time;
                result.items.emplace_back(std::make_unique<BusResponseItem>(std::move(busResponseItem)));
            } else {
                return std::nullopt;
            }
        }

        for (const auto &item: result.items) {
            result.total_time += item->time;
        }

        return PathResponse{std::move(result)};
    }

private:
    void UpdateLengths() {
        for (auto&[name, bus]: buses) {
            bus.UpdateLength(stops);
        }
    }

    [[nodiscard]] Graph::DirectedWeightedGraph<double> BuildGraph() {
        Graph::DirectedWeightedGraph<double> new_graph(stops.size() * 2);

        for (Graph::VertexId stop_idx = 0; stop_idx < indexStops.size(); stop_idx += 2) {
            double time = routingSettings.bus_wait_time;
            edges.emplace_back(WaitEdge{.stop_name = indexStops[stop_idx], .time = time});
            new_graph.AddEdge(Graph::Edge<double>{.from = stop_idx,
                    .to = stop_idx + 1,
                    .weight = time});
        }

        for (const auto &bus: buses) {
            for (auto it_first = bus.second.stops.begin(); it_first != bus.second.stops.end(); ++it_first) {
                for (auto it_second = bus.second.isRoundtrip ? next(it_first) : bus.second.stops.begin();
                     it_second != bus.second.stops.end(); ++it_second) {
                    if (*it_first == *it_second) {
                        continue;
                    }

                    std::vector<std::string> temp;
                    int span_count = 0;
                    if (it_first < it_second) {
                        temp = std::vector(it_first, next(it_second));
                        span_count = static_cast<int>(it_second - it_first);
                    } else if (it_first > it_second) {
                        temp = std::vector(it_second, next(it_first));
                        std::reverse(temp.begin(), temp.end());
                        span_count = static_cast<int>(it_first - it_second);
                    } else {
                        continue;
                    }

                    double time = Bus::CalculateCurLength(temp, stops) / (routingSettings.bus_velocity * 1000 / 60);

                    edges.emplace_back(BusEdge{.bus_name = bus.second.name,
                            .from = *it_first,
                            .to = *it_second,
                            .span_count = span_count,
                            .time = time});
                    new_graph.AddEdge(Graph::Edge<double>{.from = invertedIndexStops.at(*it_first) + 1,
                            .to = invertedIndexStops.at(*it_second),
                            .weight = time});
                }
            }
        }

        return std::move(new_graph);
    }

    void CreateRouter() {
        graph = std::make_unique<Graph::DirectedWeightedGraph<double>>(BuildGraph());
        router = std::make_unique<Graph::Router<double>>(*graph);
    }

    std::unordered_map<std::string, Bus> buses;
    std::unordered_map<std::string, Stop> stops;
    std::unordered_map<std::string, std::set<std::string>> buses_on_stop;

    RoutingSettings routingSettings;
    std::unique_ptr<Graph::DirectedWeightedGraph<double>> graph;
    std::unique_ptr<Graph::Router<double>> router;
    std::vector<std::string> indexStops;
    std::unordered_map<std::string, Graph::VertexId> invertedIndexStops;
    std::vector<std::variant<WaitEdge, BusEdge>> edges;
};