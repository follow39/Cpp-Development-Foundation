#include "render.h"

#include <algorithm>
#include <optional>

using namespace std;

namespace Render {

    RenderSettings::RenderSettings(const Json::Dict &attrs) {
        width = attrs.at("width").AsDouble();
        height = attrs.at("height").AsDouble();
        padding = attrs.at("padding").AsDouble();
        stop_radius = attrs.at("stop_radius").AsDouble();
        line_width = attrs.at("line_width").AsDouble();
        underlayer_width = attrs.at("underlayer_width").AsDouble();
        stop_label_font_size = attrs.at("stop_label_font_size").AsInt();
        stop_label_font_size = attrs.at("stop_label_font_size").AsInt();

        stop_label_offset = {attrs.at("stop_label_offset").AsArray()[0].AsDouble(),
                             attrs.at("stop_label_offset").AsArray()[1].AsDouble()};

        underlayer_color = ColorFromJson(attrs.at("underlayer_color"));

        for (const auto &item: attrs.at("color_palette").AsArray()) {
            color_palette.push_back(ColorFromJson(item));
        }
    }

    Svg::Color ColorFromJson(const Json::Node &attrs) {
        Svg::Color result;
        if (std::holds_alternative<std::string>(attrs.GetBase())) {
            result = attrs.AsString();
        } else {
            const auto &attrs_array = attrs.AsArray();
            if (attrs_array.size() == 4) {
                result = Svg::Rgb{
                        attrs_array[0].AsInt(),
                        attrs_array[1].AsInt(),
                        attrs_array[2].AsInt(),
                        attrs_array[3].AsDouble()
                };
            } else {
                result = Svg::Rgb{
                        attrs_array[0].AsInt(),
                        attrs_array[1].AsInt(),
                        attrs_array[2].AsInt()
                };
            }
        }
        return result;
    }

    std::string RenderTransportCatalog(const Descriptions::StopsDict &stops_dict,
                                       const Descriptions::BusesDict &buses_dict,
                                       const RenderSettings &renderSettings) {
        Svg::Document svgDocument;

        ZoomCoef zoomCoef{stops_dict, renderSettings};

        auto it_color = renderSettings.color_palette.begin();
        for (const auto&[busName, bus]: buses_dict) {
            Svg::Polyline busPath{};
            busPath.SetStrokeWidth(renderSettings.line_width)
                    .SetFillColor(*it_color++);
            for (const auto &stopName: bus->stops) {
                busPath.AddPoint({
                                         .x = zoomCoef.MakeZoomLon(stops_dict.at(stopName)->position.longitude),
                                         .y = zoomCoef.MakeZoomLat(stops_dict.at(stopName)->position.latitude)});
            }
            svgDocument.Add(std::move(busPath));
        }

        for (const auto&[stopName, stop]: stops_dict) {
            Svg::Circle stopCircle{};
            svgDocument.Add(Svg::Circle{}
                                    .SetCenter({zoomCoef.MakeZoomLat(stop->position.latitude),
                                                zoomCoef.MakeZoomLon(stop->position.longitude)})
                                    .SetFillColor("white")
            );
        }

        for (const auto&[stopName, stop]: stops_dict) {
            Svg::Circle stopCircle{};
            svgDocument.Add(Svg::Text{}
                                    .SetPoint({zoomCoef.MakeZoomLat(stop->position.latitude),
                                               zoomCoef.MakeZoomLon(stop->position.longitude)})
                                    .SetOffset({renderSettings.stop_label_offset.x,
                                                renderSettings.stop_label_offset.y})
                                    .SetFontSize(renderSettings.stop_label_font_size)
                                    .SetFillColor("black")
            );
        }


        std::stringstream ss;
        svgDocument.Render(ss);
        return ss.str();
    }

    ZoomCoef::ZoomCoef(const Descriptions::StopsDict &stops_dict, const RenderSettings &renderSettings) {
        min_lon = stops_dict.begin()->second->position.longitude;
        max_lon = stops_dict.begin()->second->position.longitude;
        min_lat = stops_dict.begin()->second->position.latitude;
        max_lat = stops_dict.begin()->second->position.latitude;
        padding = renderSettings.padding;
        for (const auto&[stopName, stop]: stops_dict) {
            min_lon = min(stop->position.longitude, min_lon);
            max_lon = min(stop->position.longitude, max_lon);
            min_lat = min(stop->position.latitude, min_lat);
            max_lat = max(stop->position.latitude, max_lat);
        }
        std::optional<double> width_zoom_coef;
        std::optional<double> height_zoom_coef;
        double zoom_coef = 0.0;
        if (max_lon == min_lon) {
            (renderSettings.width - 2 * renderSettings.padding) / (max_lon - min_lon);
        }
        if (max_lat != min_lat) {
            (renderSettings.height - 2 * renderSettings.padding) / (max_lat - min_lat);
        }
        if (width_zoom_coef && height_zoom_coef) {
            zoom_coef = min(width_zoom_coef.value(), height_zoom_coef.value());
        } else if (width_zoom_coef) {
            zoom_coef = height_zoom_coef.value();
        } else if (height_zoom_coef) {
            zoom_coef = width_zoom_coef.value();
        } else {
            zoom_coef = 0.0;
        }
    }

    double ZoomCoef::MakeZoomLon(double longitude) const {
        return (longitude - min_lon) * zoomCoef + padding;
    }

    double ZoomCoef::MakeZoomLat(double latitude) const {
        return (latitude - min_lat) * zoomCoef + padding;
    }

}
