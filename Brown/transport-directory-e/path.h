#pragma once

#include "graph.h"
#include "json.h"
#include "router.h"

#include <string>
#include <optional>

struct PathRequest {
    std::string from;
    std::string to;

    PathRequest() = default;

    PathRequest(const std::map<std::string, Json::Node> &request) {
        from = request.at("from").AsString();
        to = request.at("to").AsString();
    }
};

struct RoutingSettings {
    int bus_wait_time = 0;
    double bus_velocity = 0;

    RoutingSettings() = default;

    RoutingSettings(const std::map<std::string, Json::Node> &request) {
        bus_wait_time = request.at("bus_wait_time").AsInt();
        bus_velocity = request.at("bus_velocity").AsDouble();
    }
};

struct PathItem {
    std::string type;
    std::string stop_name;
    int time = 0;

    [[nodiscard]] Json::Node ToJson() const {
        std::map<std::string, Json::Node> result;
        result.emplace("type", Json::Node(type));
        result.emplace("stop_name", Json::Node(stop_name));
        result.emplace("time", Json::Node(time));
        return result;
    }
};

struct Path {
    int total_time = 0;
    std::vector<PathItem> items;


    [[nodiscard]] Json::Node ToJson() const {
        std::map<std::string, Json::Node> result;
        std::vector<Json::Node> result_items;
        for (const auto &item: items) {
            result_items.emplace_back(item.ToJson());
        }
        result.emplace("total_time", Json::Node(total_time));
        result.emplace("items", Json::Node(std::move(result_items)));
        return Json::Node{std::move(result)};
    }
};
