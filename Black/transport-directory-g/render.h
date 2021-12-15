#pragma once

#include "svg.h"
#include "json.h"
#include "descriptions.h"

#include <vector>
#include <variant>
#include <string>
#include <sstream>

namespace Render {
    struct RenderSettings {
        double width = 0.0;
        double height = 0.0;
        double padding = 0.0;
        double stop_radius = 0.0;
        double line_width = 0.0;
        double underlayer_width = 0.0;
        int stop_label_font_size = 0;
        Svg::Point stop_label_offset;
        Svg::Color underlayer_color = Svg::NoneColor;
        std::vector<Svg::Color> color_palette;

        RenderSettings() = default;

        explicit RenderSettings(const Json::Dict &attrs);
    };

    struct ZoomCoef {
        double zoomCoef = 0.0;
        double min_lon = 0.0;
        double max_lon = 0.0;
        double min_lat = 0.0;
        double max_lat = 0.0;
        double padding = 0.0;

        ZoomCoef() = delete;

        explicit ZoomCoef(const Descriptions::StopsDict &stops_dict, const RenderSettings &renderSettings);
        double MakeZoomLon(double longitude) const;
        double MakeZoomLat(double latitude) const;
    };

    Svg::Color ColorFromJson(const Json::Node &attrs);

    std::string RenderTransportCatalog(const Descriptions::StopsDict &stops_dict,
                                       const Descriptions::BusesDict &buses_dict,
                                       const RenderSettings &renderSettings);
}
