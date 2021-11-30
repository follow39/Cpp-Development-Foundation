#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cmath>

#include "json.h"

struct StopInfo {
    std::set<std::string> buses;

    Json::Node ToJson() {
        std::map<std::string, Json::Node> result;
        std::vector<Json::Node> result_buses;
        for (const auto &bus: buses) {
            result_buses.emplace_back(bus);
        }
        result.emplace("buses", Json::Node(std::move(result_buses)));
        return Json::Node(std::move(result));
    }
};

struct Stop {
    std::string name;
    double latitude = 0.0;
    double longitude = 0.0;
    std::unordered_map<std::string, double> distance_to;

    static double CalculateGeoDistance(const Stop &first, const Stop &second) {
        auto hav = [](double value) { return (1 - cos(value * M_PI / 180)) / 2; };
        const double r = 6'371'000;

        return 2 * r * asin(sqrt(hav(second.latitude - first.latitude) +
                                 (1 - hav(first.latitude - second.latitude) -
                                  hav(first.latitude + second.latitude)) *
                                 hav(second.longitude - first.longitude)));
    }

    Stop() = default;

    explicit Stop(const std::map<std::string, Json::Node> &request) {
        name = request.at("name").AsString();
        latitude = request.at("latitude").AsDouble();
        longitude = request.at("longitude").AsDouble();
        for (const auto&[stop_name, length]: request.at("road_distances").AsMap()) {
            distance_to[stop_name] = length.AsInt();
        }
    }
};

//std::string BuildJsonFromStopInfo(const StopInfo &stopInfo) {
//    std::string result;
//    result += R"("buses": )";
//    result += "[";
//    bool first = true;
//    for (const auto &bus: stopInfo.buses) {
//        if (!first) {
//            result += ",";
//        } else {
//            first = false;
//        }
//        result += "\n";
//        result += '\"' + bus + '\"';
//    }
//    result += "\n]";
//    return result;
//}