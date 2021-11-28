#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

struct Bus {
    std::string name;
    bool isCircle = false;
    double cur_length = 0.0;
    double geo_length = 0.0;
    size_t stops_count = 0;
    size_t unique_stops_count = 0;
    std::vector<std::string> stops;

    double CalculateGeoLength(const std::unordered_map<std::string, Stop> &input_stops) {
        if (stops.empty()) {
            return 0.0;
        }
        double new_length = 0.0;
        std::string prev = stops[0];
        for (const auto &current: stops) {
            new_length += Stop::CalculateGeoDistance(input_stops.at(prev), input_stops.at(current));
            prev = current;
        }
        return new_length;
    }

    double CalculateCurLength(const std::vector<std::string> &stops,
                              const std::unordered_map<std::string, Stop> &input_stops) {
        if (stops.empty()) {
            return 0.0;
        }
        double new_length = 0.0;
        std::string prev = stops[0];
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

    void UpdateLength(const std::unordered_map<std::string, Stop> &input_stops) {
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

    explicit Bus(std::string_view request) {
        request.remove_prefix(4);
        name = std::string(request.substr(0, request.find(':')));
        request.remove_prefix(request.find(':') + 2);

        char splitter;
        if (request.find('-') == std::string_view::npos) {
            isCircle = true;
            splitter = '>';
        } else {
            isCircle = false;
            splitter = '-';
        }

        while (!request.empty()) {
            stops.emplace_back(request.substr(0, request.find(splitter) - 1));
            if (request.find(splitter) == std::string_view::npos) {
                break;
            }
            request.remove_prefix(std::min(request.find(splitter) + 2, request.size())
            );
        }

        stops_count = isCircle ? stops.size() : (stops.size() * 2 - 1);
//        unique_stops_count = isCircle ? ((stops.size() + 1) / 2) : stops.size();
        std::unordered_set<std::string> unique_stops(stops.begin(), stops.end());
        unique_stops_count = unique_stops.size();
    }
};