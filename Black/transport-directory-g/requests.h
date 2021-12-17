#pragma once

#include "json.h"
#include "transport_catalog.h"
#include "render.h"

#include <string>
#include <variant>

#define DEBUGIO 1

namespace Requests {
    struct Stop {
        std::string name;

        [[nodiscard]] Json::Dict Process(const TransportCatalog &db) const;
    };

    struct Bus {
        std::string name;

        [[nodiscard]] Json::Dict Process(const TransportCatalog &db) const;
    };

    struct Route {
        std::string stop_from;
        std::string stop_to;

        [[nodiscard]] Json::Dict Process(const TransportCatalog &db) const;
    };

    struct SvgMap {
//        Svg::Document document;
//        Render::RenderSettings renderSettings;

        [[nodiscard]] Json::Dict Process(const TransportCatalog &db) const;
    };

    std::variant<Stop, Bus, Route, SvgMap> Read(const Json::Dict &attrs);

    std::vector<Json::Node> ProcessAll(const TransportCatalog &db, const std::vector<Json::Node> &requests);
}
