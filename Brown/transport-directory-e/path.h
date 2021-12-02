#pragma once

#include "json.h"

#include <string>
#include <memory>

struct RoutingSettings {
    int bus_wait_time = 0;
    double bus_velocity = 0;

    RoutingSettings() = default;

    explicit RoutingSettings(const std::map<std::string, Json::Node> &request) {
        bus_wait_time = request.at("bus_wait_time").AsInt();
        bus_velocity = request.at("bus_velocity").AsDouble();
    }
};

struct PathRequest {
    std::string from;
    std::string to;

    PathRequest() = default;

    explicit PathRequest(const std::map<std::string, Json::Node> &request) {
        from = request.at("from").AsString();
        to = request.at("to").AsString();
    }
};

struct PathResponseItem {
    std::string type;
    double time = 0;

    [[nodiscard]] virtual Json::Node ToJson() const = 0;

    virtual ~PathResponseItem() = default;
};

struct WaitResponseItem : public PathResponseItem {
    std::string stop_name;

    WaitResponseItem() {
        type = "Wait";
    }

    [[nodiscard]] Json::Node ToJson() const override {
        std::map<std::string, Json::Node> result;
        result.emplace("type", Json::Node(type));
        result.emplace("time", Json::Node(static_cast<int>(time)));
        result.emplace("stop_name", Json::Node(stop_name));
        return Json::Node{std::move(result)};
    }
};

struct BusResponseItem : public PathResponseItem {
    std::string bus_name;
    int span_count = 0;

    BusResponseItem() {
        type = "Bus";
    }

    [[nodiscard]] Json::Node ToJson() const override {
        std::map<std::string, Json::Node> result;
        result.emplace("type", Json::Node(type));
        result.emplace("time", Json::Node(time));
        result.emplace("bus", Json::Node(bus_name));
        result.emplace("span_count", Json::Node(span_count));
        return Json::Node{std::move(result)};
    }
};

struct PathResponse {
    double total_time = 0;
    std::vector<std::unique_ptr<PathResponseItem>> items;

    [[nodiscard]] Json::Node ToJson() const {
        std::map<std::string, Json::Node> result;
        std::vector<Json::Node> result_items;
        for (const auto &item: items) {
            result_items.emplace_back(item->ToJson());
        }
        result.emplace("items", Json::Node(std::move(result_items)));
        result.emplace("total_time", Json::Node(total_time));
        return Json::Node{std::move(result)};
    }
};
