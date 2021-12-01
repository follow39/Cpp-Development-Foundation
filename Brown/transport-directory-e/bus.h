#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

struct BusInfo {
    std::string name;
    double length = 0.0;
    int stops_count = 0;
    int unique_stops_count = 0;
    double curvature = 0.0;

    [[nodiscard]] Json::Node ToJson() const {
        std::map<std::string, Json::Node> result;
        result.emplace("route_length", Json::Node(length));
        result.emplace("curvature", Json::Node(curvature));
        result.emplace("stop_count", Json::Node(stops_count));
        result.emplace("unique_stop_count", Json::Node(unique_stops_count));
        return Json::Node{std::move(result)};
    }
};

struct Bus {
    std::string name;
    bool isCircle = false;
    double cur_length = 0.0;
    double geo_length = 0.0;
    int stops_count = 0;
    int unique_stops_count = 0;
    double curvature = 0.0;
    std::vector<std::string> stops;

    static double CalculateGeoLength(const std::vector<std::string> &stops_vec,
                                     const std::unordered_map<std::string, Stop> &input_stops) {
        if (stops_vec.empty()) {
            return 0.0;
        }
        double new_length = 0.0;
        std::string prev = stops_vec[0];
        for (const auto &current: stops_vec) {
            new_length += Stop::CalculateGeoDistance(input_stops.at(prev), input_stops.at(current));
            prev = current;
        }
        return new_length;
    }

    static double CalculateCurLength(const std::vector<std::string> &stops_vec,
                                     const std::unordered_map<std::string, Stop> &input_stops) {
        if (stops_vec.empty()) {
            return 0.0;
        }
        double new_length = 0.0;
        std::string prev = stops_vec[0];
        for (const auto &current: stops_vec) {
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

    void UpdateLength(const std::unordered_map<std::string, Stop> &input_stops) {
        geo_length = CalculateGeoLength(stops, input_stops);
        if (!isCircle) {
            geo_length *= 2;
        }

        cur_length = CalculateCurLength(stops, input_stops);
        if (!isCircle) {
            auto temp_stops = stops;
            reverse(temp_stops.begin(), temp_stops.end());
            cur_length += CalculateCurLength(temp_stops, input_stops);
        }

        curvature = cur_length / geo_length;
    }

    void UpdateStopsCounters() {
        stops_count = isCircle ? stops.size() : (stops.size() * 2 - 1);
//        unique_stops_count = isCircle ? ((stops.size() + 1) / 2) : stops.size();
        std::unordered_set<std::string> unique_stops(stops.begin(), stops.end());
        unique_stops_count = unique_stops.size();
    }

    [[nodiscard]] BusInfo GetBusInfo() const {
        return BusInfo{.name = name,
                .length = cur_length,
                .stops_count = stops_count,
                .unique_stops_count = unique_stops_count,
                .curvature = curvature};
    }

    Bus() = default;

    explicit Bus(const std::map<std::string, Json::Node> &request) {
        name = request.at("name").AsString();
        isCircle = request.at("is_roundtrip").AsBool();
        for (const auto &stop_name: request.at("stops").AsArray()) {
            stops.push_back(stop_name.AsString());
        }
        UpdateStopsCounters();
    }
};
