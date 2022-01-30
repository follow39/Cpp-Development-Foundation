#include "svg.h"


namespace Svg {

    void RenderPoint(std::ostream &output, const Point &point) {
        output << std::to_string(point.x) << ","
               << std::to_string(point.y);
    }

    void RenderRgb(std::ostream &output, const Rgb &rgb) {
        output << "rgb("
               << std::to_string(rgb.red) << ","
               << std::to_string(rgb.green) << ","
               << std::to_string(rgb.blue) << ")";
    }

    void RenderRgba(std::ostream &output, const Rgba &rgba) {
        output << "rgba("
               << std::to_string(rgba.red) << ","
               << std::to_string(rgba.green) << ","
               << std::to_string(rgba.blue) << ","
               << std::to_string(rgba.alpha) << ")";
    }

    void RenderColor(std::ostream &output, std::monostate) {
        output << "none";
    }

    void RenderColor(std::ostream &output, const std::string &color) {
        output << color;
    }

    void RenderColor(std::ostream &output, const Rgb &color) {
        RenderRgb(output, color);
    }

    void RenderColor(std::ostream &output, const Rgba &color) {
        RenderRgba(output, color);
    }

    template<typename ParamType>
    void RenderParam(std::ostream &output, const std::string &paramName, const ParamType &paramValue) {
        output << paramName << "=\""
               << paramValue << "\" ";
    }

    template<>
    void RenderParam(std::ostream &output, const std::string &paramName, const Color &paramValue) {
        output << paramName + "=\"";
        std::visit([&output](const auto &color) { RenderColor(output, color); },
                   paramValue);
        output << "\" ";
    }

    template<typename ObjectType>
    void SvgObject<ObjectType>::RenderAttrs(std::ostream &output) const {
        RenderParam(output, "fill", fillColor);
        RenderParam(output, "stroke", strokeColor);
        RenderParam(output, "stroke-width", strokeWidth);
        if (!strokeLineCap.empty()) {
            RenderParam(output, "stroke-linecap", strokeLineCap);
        }
        if (!strokeLineJoin.empty()) {
            RenderParam(output, "stroke-linejoin", strokeLineJoin);
        }
    }


    void Circle::Render(std::ostream &output) const {
        output << "<circle ";
        RenderParam(output, "cx", std::to_string(center.x));
        RenderParam(output, "cy", std::to_string(center.y));
        RenderParam(output, "r", std::to_string(radius));
        SvgObject::RenderAttrs(output);
        output << "/>";
    }

    void Polyline::Render(std::ostream &output) const {
        output << "<polyline ";
        output << "points=\"";
        for (const auto &point: points) {
            RenderPoint(output, point);
            output << ' ';
        }
        output << "\" ";
        SvgObject::RenderAttrs(output);
        output << "/>";
    }

    void Text::Render(std::ostream &output) const {
        output << "<text ";
        RenderParam(output, "x", point.x);
        RenderParam(output, "y", point.y);
        RenderParam(output, "dx", offset.x);
        RenderParam(output, "dy", offset.y);
        RenderParam(output, "font-size", fontSize);
        if (!fontWeight.empty()) {
            RenderParam(output, "font-weight", fontWeight);
        }
        if (!fontFamily.empty()) {
            RenderParam(output, "font-family", fontFamily);
        }
        SvgObject::RenderAttrs(output);
        output << ">" << text << "</text>";
    }

    void Document::Render(std::ostream &output) const {
        output << xmlVersion;
        output << svgBegin;
        for (const auto &object: objects) {
            object->Render(output);
        }
        output << svgEnd;
    }

}
