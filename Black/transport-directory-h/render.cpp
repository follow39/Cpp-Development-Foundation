#include "render.h"

#include <algorithm>
#include <set>

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

        stop_label_offset = {
                attrs.at("stop_label_offset").AsArray()[0].AsDouble(),
                attrs.at("stop_label_offset").AsArray()[1].AsDouble()
        };

        underlayer_color = ColorFromJson(attrs.at("underlayer_color"));

        for (const auto &item: attrs.at("color_palette").AsArray()) {
            color_palette.push_back(ColorFromJson(item));
        }
    }

    Svg::Color ColorFromJson(const Json::Node &attrs) {
        Svg::Color result;
        if (std::holds_alternative<std::string>(attrs.GetBase())) {
            result = attrs.AsString();
        } else if (std::holds_alternative<std::vector<Json::Node>>(attrs.GetBase())) {
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
        } else {
            result = Svg::NoneColor;
        }
        return result;
    }

    std::string RenderTransportCatalog(const Descriptions::StopsDict &stops_dict,
                                       const Descriptions::BusesDict &buses_dict,
                                       const RenderSettings &renderSettings) {
        Svg::Document svgDocument;
        ZoomCoef zoomCoef{stops_dict, renderSettings};

        std::set<std::string> stops;
        std::set<std::string> buses;

        for (const auto&[stopName, _]: stops_dict) {
            stops.insert(stopName);
        }
        for (const auto&[busName, _]: buses_dict) {
            buses.insert(busName);
        }

        auto it_color = renderSettings.color_palette.begin();
        for (const auto &busName: buses) {
            if (it_color == renderSettings.color_palette.end()) {
                it_color = renderSettings.color_palette.begin();
            }
            Svg::Polyline busPath{};
            busPath.SetStrokeWidth(renderSettings.line_width)
                    .SetStrokeColor(*it_color++)
                    .SetStrokeLineCap("round")
                    .SetStrokeLineJoin("round");
            for (const auto &stopName: buses_dict.at(busName)->stops) {
//                stops.insert(stopName);
                busPath.AddPoint({
                                         .x = zoomCoef.MakeZoomLon(stops_dict.at(stopName)->position.longitude),
                                         .y = zoomCoef.MakeZoomLat(stops_dict.at(stopName)->position.latitude)
                                 }
                );
            }
            svgDocument.Add(std::move(busPath));
        }

        for (const auto &stopName: stops) {
//            std::cout << stopName << ": "
//                      << zoomCoef.MakeZoomLon(stops_dict.at(stopName)->position.longitude) << " - "
//                      << zoomCoef.MakeZoomLat(stops_dict.at(stopName)->position.latitude) << " <> "
//                      << stops_dict.at(stopName)->position.longitude << " - "
//                      << stops_dict.at(stopName)->position.latitude << std::endl;
            svgDocument.Add(Svg::Circle{}
                                    .SetCenter({
                                                       .x = zoomCoef.MakeZoomLon(
                                                               stops_dict.at(stopName)->position.longitude),
                                                       .y = zoomCoef.MakeZoomLat(
                                                               stops_dict.at(stopName)->position.latitude)
                                               })
                                    .SetRadius(renderSettings.stop_radius)
                                    .SetFillColor("white")
            );
        }

        for (const auto &stopName: stops) {
            svgDocument.Add(Svg::Text{}
                                    .SetPoint({
                                                      .x = zoomCoef.MakeZoomLon(
                                                              stops_dict.at(stopName)->position.longitude),
                                                      .y = zoomCoef.MakeZoomLat(
                                                              stops_dict.at(stopName)->position.latitude)
                                              })
                                    .SetOffset({
                                                       .x = renderSettings.stop_label_offset.x,
                                                       .y = renderSettings.stop_label_offset.y
                                               })
                                    .SetFontSize(renderSettings.stop_label_font_size)
                                    .SetFontFamily("Verdana")
                                    .SetFillColor("black")
                                    .SetData(stopName)
                                    .SetFillColor(renderSettings.underlayer_color)
                                    .SetStrokeColor(renderSettings.underlayer_color)
                                    .SetStrokeWidth(renderSettings.underlayer_width)
                                    .SetStrokeLineCap("round")
                                    .SetStrokeLineJoin("round")
            );
            svgDocument.Add(Svg::Text{}
                                    .SetPoint({
                                                      .x = zoomCoef.MakeZoomLon(
                                                              stops_dict.at(stopName)->position.longitude),
                                                      .y = zoomCoef.MakeZoomLat(
                                                              stops_dict.at(stopName)->position.latitude)
                                              })
                                    .SetOffset({
                                                       .x = renderSettings.stop_label_offset.x,
                                                       .y = renderSettings.stop_label_offset.y
                                               })
                                    .SetFontSize(renderSettings.stop_label_font_size)
                                    .SetFontFamily("Verdana")
                                    .SetFillColor("black")
                                    .SetData(stopName)
            );
        }

        std::stringstream ss;
        svgDocument.Render(ss);
        return ss.str();
    }

    ZoomCoef::ZoomCoef(const Descriptions::StopsDict &stops_dict, const RenderSettings &renderSettings) {
        if (!stops_dict.empty()) {
            minLon = stops_dict.begin()->second->position.longitude;
            maxLon = stops_dict.begin()->second->position.longitude;
            minLat = stops_dict.begin()->second->position.latitude;
            maxLat = stops_dict.begin()->second->position.latitude;
        }
        padding = renderSettings.padding;
        for (const auto&[_, stop]: stops_dict) {
            minLon = min(stop->position.longitude, minLon);
            maxLon = max(stop->position.longitude, maxLon);
            minLat = min(stop->position.latitude, minLat);
            maxLat = max(stop->position.latitude, maxLat);
        }
        if (fabs(maxLon - minLon) >= epsilon) {
            widthZoomCoef = (renderSettings.width - 2 * renderSettings.padding) / (maxLon - minLon);
        }
        if (fabs(maxLat - minLat) >= epsilon) {
            heightZoomCoef = (renderSettings.height - 2 * renderSettings.padding) / (maxLat - minLat);
        }
        if (widthZoomCoef && heightZoomCoef) {
            zoomCoef = min(widthZoomCoef.value(), heightZoomCoef.value());
        } else if (widthZoomCoef) {
            zoomCoef = widthZoomCoef.value();
        } else if (heightZoomCoef) {
            zoomCoef = heightZoomCoef.value();
        } else {
            zoomCoef = 0.0;
        }
    }

    double ZoomCoef::MakeZoomLon(double longitude) const {
        return (longitude - minLon) * zoomCoef + padding;
    }

    double ZoomCoef::MakeZoomLat(double latitude) const {
        return (maxLat - latitude) * zoomCoef + padding;
    }

}
