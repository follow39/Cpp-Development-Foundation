#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cmath>

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

    explicit Stop(std::string_view request) {
        request.remove_prefix(5);
        name = std::string(request.substr(0, request.find(':')));
        request.remove_prefix(request.find(':') + 2);
        latitude = stod(std::string(request.substr(0, request.find(','))));
        request.remove_prefix(request.find(',') + 2);
        longitude = stod(std::string(request.substr(0, request.find(','))));
        request.remove_prefix(request.find(',') + 2);

        while (request.find(" to ") != std::string_view::npos) {
//        while (!request.empty()) {
            double distance = stod(std::string(request.substr(0, request.find('m'))));
            request.remove_prefix(request.find("to") + 3);
            std::string stop_name = std::string(request.substr(0, request.find(',')));
            request.remove_prefix(request.find(',') + 2);

            distance_to[stop_name] = distance;
        }
    }
};